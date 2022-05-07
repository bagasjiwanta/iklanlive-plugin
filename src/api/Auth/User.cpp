// Created by bayus on 07/05/22.
//

#include "../../exception/ConfigException.h"
#include "User.h"
#include <obs-module.h>
#include "../../plugin-config.h"

namespace Auth {

  User::User() : token(""), is_logged(false) {}

  void User::from_config(const config_t *config) {
    config_t * conf = const_cast<config_t *>(config);
    blog(LOG_INFO, "HALOO");
    const char* auth_token = config_get_string(conf, "auth", "token");
    bool is_logged = config_get_bool(conf, "auth", "is_logged");

    if(!auth_token) {
      this->token = "";
      throw new ConfigException(FORMAT_ERROR, "AUTH_TOKEN is not found");
    }

    this->token = auth_token;
    this->is_logged = is_logged;
  }

  void User::to_config(config_t *config) {
    config_set_string(config, "auth","token",this->token.c_str());
    config_set_bool(config, "auth", "is_logged", this->is_logged);
  }

  const string &User::getToken() const {
    return this->token;
  }

  void User::setToken(const string &token) {
    User::token = token;
  }

  bool User::isLogged() const {
    return is_logged;
  }

  void User::setIsLogged(bool isLogged) {
    is_logged = isLogged;
  }
} // Auth