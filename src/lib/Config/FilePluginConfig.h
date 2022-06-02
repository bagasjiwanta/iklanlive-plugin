//
// Created by bayus on 02/06/22.
//

#ifndef IKLANLIVE_PLUGIN_FILEPLUGINCONFIG_H
#define IKLANLIVE_PLUGIN_FILEPLUGINCONFIG_H

#include "plugin-macros.generated.h"
#include <util/config-file.h>
#include <string>

class FilePluginConfig {
protected:
  config_t* config;
  std::string path;

public:
  virtual config_t* open_config() = 0;
  std::string get_path();
  void close_config();
  void save_config();
};


#endif //IKLANLIVE_PLUGIN_FILEPLUGINCONFIG_H
