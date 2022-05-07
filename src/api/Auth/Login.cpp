//
// Created by bayus on 07/05/22.
//

#include "./Login.h"
#include <nlohmann/json.hpp>
#include "../../plugin-config.h"
#include "./User.h"
#include <util/config-file.h>
#include <cpr/cpr.h>
#include <iostream>
#include <string>
#include "../../plugin-macros.generated.h"

using json = nlohmann::json;

Auth::User Auth::login(const string& email, const string& password) {
    // simple validation
    Auth::User user = config.getActiveUser();
    
    if(email.length() == 0 || password.length() == 0) {
        return user;
    }

    std::string backend_url = BACKEND_URL;
    std::string request_url = backend_url + "/login";

    json body;
    body["email"] = email;
    body["password"] = password;
    body["rememberMe"] = true;

    cpr::Response r = cpr::Post(
        cpr::Url{request_url},
        cpr::Header{
            {"accept", "application/json"}, 
            {"content-type", "application/json"}
        },
        cpr::Body{ body.dump() }
    );

    // bad request
    if(r.status_code >= 300) {
        return user;
    }   

    auto j = json::parse(r.text);

    // check if body valid
    if (
        (!(j.contains("token"))) || 
        (!(j.contains("status"))) ||
        (!(j["token"].is_string()))
    ) { return user; }

    std::string token = j["token"].get<std::string>();

    user.setToken(token);
    user.setIsLogged(true);
    return user;
}
