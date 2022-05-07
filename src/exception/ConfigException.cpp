//
// Created by bayus on 07/05/22.
//

#include "ConfigException.h"

#include <utility>
#include <string>

std::string ConfigException::to_string() {
  if(this->err == FILE_NOT_FOUND){
    return "Error parsing config because file not found";
  }else if(this->err == FORMAT_ERROR){
    return "Config is not in valid format: " + this->description;
  }
}

ConfigException::ConfigException(config_error_type err, std::string description) {
  this->err = err;
  this->description = std::move(description);
}
