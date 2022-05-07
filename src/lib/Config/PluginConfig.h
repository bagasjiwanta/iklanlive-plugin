//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_PLUGINCONFIG_H
#define IKLANLIVE_PLUGIN_PLUGINCONFIG_H

#include "api/Auth/User.h"
#include <util/config-file.h>
#include <string>

using namespace std;

namespace Config{
  class PluginConfig {
    Auth::User activeUser;
  public:
    Auth::User &getActiveUser();

  public:
    void write_config();
    void load_config();
  };

  PluginConfig load_config();
}

#endif //IKLANLIVE_PLUGIN_PLUGINCONFIG_H
