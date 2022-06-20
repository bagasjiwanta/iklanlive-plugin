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
#include <vector>
#include "../exception/AuthException.h"
#include "../exception/LivestreamException.h"

using json = nlohmann::json;

std::time_t str_to_timestamp(const std::string &str)
{
	struct std::tm tm;
	std::istringstream ss(str.c_str());
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	if (ss.fail()) {
		// throw exception
		return 0;
	}

	std::time_t timestamp = mktime(&tm);
	return timestamp;
}

bool isTimestampPassed(time_t t)
{
	// blog(LOG_INFO, "time : %lld, now : %lld", t, time(NULL));
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

	if (r.error) {
		throw new LivestreamException(
			UNKNOWN_LIVESTREAM_ERROR,
			"Error while fetching stream url");
	}

	if (r.status_code == 200) {
		auto j = json::parse(r.text);

		if (j.contains("data") && j["data"].contains("stream_token") &&
		    j["data"]["stream_token"].is_string()) {
			std::string stream_url =
				"http://localhost:3000/embedd/" +
				j["data"]["stream_token"].get<std::string>();
			blog(LOG_INFO, "stream url : %s", stream_url.c_str());
			return stream_url.c_str();
		}
	}

	if (r.status_code == 403 || r.status_code == 401) {
		throw new AuthException(UNAUTHORIZED, "Login Again");
	}

	return "https://obsproject.com/browser-source";
}

obs_source_t *create_browser_source(const char *link)
{
	blog(LOG_INFO, "Creating browser source with link %s", link);
	const char *browser = obs_module_text("browser_source");

	blog(LOG_INFO, "Browser id: %s", browser);

	obs_data_t *settings = obs_get_source_defaults(browser);
	obs_data_set_string(settings, "url", link);
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

	std::vector<livestream_session> lv;
	cpr::Response r =
		cpr::Get(cpr::Url{request_url},
			 cpr::Bearer{config.getActiveUser().getToken().c_str()},
			 cpr::Body{page.dump()});

	if (r.error) {
		throw new LivestreamException(UNKNOWN_LIVESTREAM_ERROR,
					      "Error in retrieving data");
	}

	if (r.status_code == 403) {
		throw new AuthException(UNAUTHORIZED, "Sign in again");
	}
	try {
		auto j = json::parse(r.text);

		if (!j.contains("data")) {
			throw new LivestreamException(
				INVALID_FORMAT, "Invalid response format");
		}

		j = j["data"];

		for (auto &i : j) {
			if (i["timestamp_end"].is_string() &&
			    isTimestampPassed(str_to_timestamp(
				    i["timestamp_end"].get<std::string>()))) {
				continue;
			}

			if (i["timestamp_start"].is_null()) {
				continue;
			}

			livestream_session l;
			if (i["name"].is_string()) {
				l.name = i["name"].get<std::string>();
			}

			l.utc_start_timestamp =
				str_to_timestamp(i["timestamp_start"]);
			l.status = i["status"].get<std::string>();
			l.stream_id = i["id"].get<int>();
			lv.push_back(l);

			// blog(LOG_INFO, "info. id : %d, ts : %lld", l.stream_id,
			//      l.utc_start_timestamp);
		}
		page["page"] = (int)(page["page"].get<int>() + 1);
	} catch (json::parse_error &e) {
		blog(LOG_ERROR, "parse error");
		throw new LivestreamException(PARSE_ERROR,
					      "Error in parsing data");
	}

	if (lv.empty()) {
		throw new LivestreamException(
			NO_AVAILABLE_LIVESTREAM,
			"No available livestream to display ads");
	}

	std::sort(lv.begin(), lv.end(), compare_start_ts);
	blog(LOG_INFO, "most recent : %d", lv.at(0).stream_id);
	return lv.at(0);
}

bool compare_start_ts(livestream_session s1, livestream_session s2)
{
	return s1.utc_start_timestamp < s2.utc_start_timestamp;
}

/* 

For future use 

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

*/
