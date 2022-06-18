//
// Created by bayus on 26/05/22.
//

#include "./util.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "../plugin-macros.generated.h"
#include "../plugin-config.h"
#include <iostream>
#include <string>
#include "./types.h"
#include "time.h"

using json = nlohmann::json;

std::time_t str_to_timestamp(const std::string &str)
{
	struct std::tm tm;
	std::istringstream ss(str.c_str());
	ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
	if (ss.fail()) {
		// throw exception
		return 0;
	}

	std::time_t timestamp = mktime(&tm);
	return timestamp;
}

bool isTimestampPassed(time_t t)
{
	return std::difftime(t, time(NULL)) < 0;
}

std::string str_tolower(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(),
		       [](unsigned char c) { return std::tolower(c); });
	return s;
}

const char *get_url_string(uint32_t id)
{
	std::string base_url = BACKEND_URL;
	std::string request_url =
		base_url + "/generateLivestreamToken/" + std::to_string(id);

	cpr::Response r =
		cpr::Get(cpr::Url{request_url},
			 cpr::Bearer{config.getActiveUser().getToken()});

	if (r.status_code == 401) {
		return "";
	}

	// auto j = json::parse(r.text);

	// if (j.contains("data") && j["data"].contains("stream_token") &&
	//     j["data"]["stream_token"].is_string()) {
	// 	std::string stream_url =
	// 		"https://iklanlive.com/embedd/" +
	// 		j["data"]["stream_token"].get<std::string>();
	// 	return stream_url.c_str();
	// }
	return "https://google.com/";

	// return "";
}

obs_source_t *create_browser_source(const char *link)
{
	blog(LOG_INFO, "Creating browser source with link %s", link);
	const char *browser = obs_module_text("browser_source");

	blog(LOG_INFO, "Browser id: %s", browser);

	obs_data_t *settings = obs_get_source_defaults(browser);
	obs_source_t *source;

	//  obs_data_set_int(settings, "color", 0xF47C7Cff);
	//  obs_data_set_string(settings, "file", "/home/bayus/Pictures/bikinibottom.jpg");
	source = obs_source_create_private(browser, nullptr, settings);

	obs_data_release(settings);

	blog(LOG_INFO, "Browser source created successfully");

	return source;
}

void update_browser_source(obs_source_t *source, const char *link)
{
	obs_data_t *settings = obs_data_create();

	obs_data_set_string(settings, "url", link);
	obs_source_update(source, settings);

	obs_data_release(settings);
}

livestream_session getClosestLivestream()
{
	std::string backend_url = BACKEND_URL;
	std::string request_url = backend_url + "/livestreams";

	json page;
	page["page"] = (int)1;

	livestream_session x;
	blog(LOG_INFO, "Start2");

	cpr::Response r =
		cpr::Get(cpr::Url{request_url},
			 cpr::Bearer{config.getActiveUser().getToken().c_str()},
			 cpr::Body{page.dump()});

	if (r.error) {
		return x;
	}

	if (r.status_code >= 400) {
		return x;
	}

	try {
		auto j = json::parse(r.text);

		if (!j.contains("data")) {
			return x;
		}

		j = j["data"];

		for (auto &i : j) {
			if (isTimestampPassed(
				    str_to_timestamp(i["timestamp_start"]))) {
				continue;
			}

			if (str_tolower(i["status"].get<std::string>()) ==
			    "started") {

				x.name = i["name"].get<std::string>();
				x.utc_start_timestamp =
					str_to_timestamp(i["timestamp_start"]);
				x.status = i["status"].get<std::string>();
				x.stream_id = i["id"].get<int>();
				return x;
			}
		}
		page["page"] = (int)(page["page"].get<int>() + 1);
	} catch (json::parse_error &e) {
		blog(LOG_ERROR, "parse error");
	}
	return x;
}

bool isLivestreamStarted(int livestreamId)
{
	if (!config.getActiveUser().isLogged()) {
		// throw exception
	}

	std::string backend_url = BACKEND_URL;
	std::string request_url = backend_url + "/getLivestreamDetails/" +
				  std::to_string(livestreamId);

	cpr::Response r = cpr::Get(
		cpr::Url{request_url},
		cpr::Bearer{config.getActiveUser().getToken().c_str()});

	if (r.status_code >= 400) {
		// throw exception
	}

	auto j = json::parse(r.text);

	if (j.contains("data") && j["data"].contains("status") &&
	    j["data"]["status"].is_string()) {
		std::string status = j["data"]["status"].get<std::string>();
		return str_tolower(status) != "started";
	}

	return false;
};
