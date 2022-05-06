//
// Created by bayus on 07/05/22.
//

#include "Login.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Auth::User Auth::login(const string& username, const string& password) {
  json payload;

}