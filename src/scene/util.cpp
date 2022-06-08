//
// Created by bayus on 26/05/22.
//

#include "util.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "../plugin-macros.generated.h"
#include "../plugin-config.h"
#include <iostream>
#include <string>

using json = nlohmann::json;

const char* get_url_string(uint32_t id) {
  if (!config.getActiveUser().isLogged()) {
    // throw exception
    return "";
  }
  
  std::string base_url = BACKEND_URL;
  std::string request_url = base_url + "/generateLivestreamToken/" + std::to_string(id);

  cpr::Response r = cpr::Get(
    cpr::Url{request_url},
    cpr::Bearer{config.getActiveUser().getToken()}
  );

  if (r.status_code >= 400) {
    // throw exception
    return "";
  }

  auto j = json::parse(r.text);

  if (
    j.contains("data") &&
    j["data"].contains("stream_token") &&
    j["data"]["stream_token"].is_string()
  ) {
    std::string stream_url = "https://iklanlive.com/embedd/" + j["data"]["stream_token"].get<std::string>();
    return stream_url.c_str();
  }

  char* res = (char*) "https://www.google.com";
  return res;
}

obs_source_t* create_browser_source(const char* link) {
  blog(LOG_INFO, "Creating browser source with link %s", link);
  const char* browser = obs_module_text("browser_source");

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

void update_browser_source(obs_source_t *source, const char* link) {
  obs_data_t *settings = obs_data_create();

  obs_data_set_string(settings, "url", link);
  obs_source_update(source, settings);

  obs_data_release(settings);
}

std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
        [](unsigned char c){ return std::tolower(c); } 
    );
    return s;
}

// return type bakal diganti
void getClosestLivestream () {
    if(!config.getActiveUser().isLogged()) {
        // throw exception
        return;
    }

    std::string backend_url = BACKEND_URL;
    std::string request_url = backend_url + "/livestreams";

    cpr::Response r = cpr::Get(
        cpr::Url{request_url},
        cpr::Bearer{config.getActiveUser().getToken().c_str()}
    );

    if (r.status_code >= 400) {
        return;
    }

    auto j = json::parse(r.text);
    // todo : get the closest / recurring livestream to now's time
}

bool isLivestreamStarted (int livestreamId) {
    if(!config.getActiveUser().isLogged()) {
        // throw exception
    }

    std::string backend_url = BACKEND_URL;
    std::string request_url = backend_url + "/getLivestreamDetails/" + std::to_string(livestreamId);
    
    cpr::Response r = cpr::Get(
        cpr::Url{request_url},
        cpr::Bearer{config.getActiveUser().getToken().c_str()}
    );

    if (r.status_code >= 400) {
        // throw exception
    }

    auto j = json::parse(r.text);
    
    if (
        j.contains("data") &&
        j["data"].contains("status") &&
        j["data"]["status"].is_string()
    ) {
        std::string status = j["data"]["status"].get<std::string>();
        return str_tolower(status) != "started";
    } 

    return false;
};