//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_CONFIGEXCEPTION_H
#define IKLANLIVE_PLUGIN_CONFIGEXCEPTION_H

#include "BaseException.h"

enum config_error_type {
  FILE_NOT_FOUND,
  FORMAT_ERROR
};

class ConfigException: public BaseException {
  config_error_type err;
  string description;

public:

  ConfigException(config_error_type err, string description = "");

  string to_string() override;

};


#endif //IKLANLIVE_PLUGIN_CONFIGEXCEPTION_H
