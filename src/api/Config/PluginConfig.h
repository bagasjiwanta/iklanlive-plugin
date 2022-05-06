//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_PLUGINCONFIG_H
#define IKLANLIVE_PLUGIN_PLUGINCONFIG_H

#include "../Auth/User.h"
#include <util/config-file.h>
#include <string>
using namespace std;

namespace Config{
  class PluginConfig {
    Auth::User activeUser;
  };

  PluginConfig load_config();
}

#ifdef __linux__
  #include <unistd.h>
  #include <sys/types.h>
  #include <pwd.h>

  struct passwd *pw = getpwuid(getuid());
  const string CONFIG_DIR = string(pw->pw_dir) + "/.iklanlive";

#elif _WIN32

  const string CONFIG_DIR = string(pw->pw_dir);
#else
  const string CONFIG_DIR = ".";
#endif


#endif //IKLANLIVE_PLUGIN_PLUGINCONFIG_H
