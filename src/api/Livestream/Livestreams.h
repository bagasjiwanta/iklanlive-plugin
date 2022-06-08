#ifndef IKLANLIVE_PLUGIN_LIVESTREAMS_H
#define IKLANLIVE_PLUGIN_LIVESTREAMS_H

#include "../../plugin-config.h"
#include "../../plugin-macros.generated.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
        [](unsigned char c){ return std::tolower(c); } 
    );
    return s;
}

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

#endif // IKLANLIVE_PLUGIN_LIVESTREAMS_H