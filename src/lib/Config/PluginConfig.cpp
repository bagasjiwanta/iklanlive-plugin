//
// Created by bayus on 07/05/22.
//
#include "plugin-macros.generated.h"
#include "exception/ConfigException.h"
#include "./PluginConfig.h"
#include "lib/Observer/ObserverInstance.h"
#include <string>
using namespace std;

#ifdef __linux__
  #include <unistd.h>
  #include <pwd.h>

  struct passwd *pw = getpwuid(getuid());
  const std::string CONFIG_DIR = string(pw->pw_dir) + "/.config/iklanlive.conf";

#elif _WIN32
  const std::string CONFIG_DIR = "/";

#else
  const string CONFIG_DIR = ".";
#endif


void Config::PluginConfig::write_config() {
  blog(LOG_INFO, "Start to write config");

  config_t* config = config_create(CONFIG_DIR.c_str());

  this->activeUser.to_config(config);

  int result = config_save_safe(config, ".conf", ".old.conf");

  switch (result) {
    case CONFIG_SUCCESS:
      blog(LOG_INFO, "Config written successfully");
      break;
    case CONFIG_FILENOTFOUND:
      blog(LOG_ERROR, "Failed to write config due to file not found error");
      break;
    default:
      blog(LOG_ERROR, "Failed to write config due to unknown error");
  }

  config_close(config);
}

void Config::PluginConfig::load_config() {
  config_t* config = nullptr;
  int result = config_open(&config, CONFIG_DIR.c_str(), CONFIG_OPEN_EXISTING);

  if(result == CONFIG_FILENOTFOUND){
    blog(LOG_INFO, "Config at %s is not available. Creating the new one.", CONFIG_DIR.c_str());
    this->write_config();
    return;
  }else if(result != CONFIG_SUCCESS){
    blog(LOG_ERROR, "Config can't be loaded due to unknown error. It may be caused by your permissions. Config Path : %s", CONFIG_DIR.c_str());
    return;
  }

  try{
    blog(LOG_INFO, "Start to load config. Config path : %s", CONFIG_DIR.c_str());
    this->activeUser.from_config(config);
  }catch(ConfigException* err){
    blog(LOG_ERROR, "Config loading error:\n%s", err->to_string().c_str());
  }

  blog(LOG_INFO, "Config Loading success");
  config_close(config);

  Observer::get_observer()->notify("update-menu");
}

Auth::User &Config::PluginConfig::getActiveUser() {
  return activeUser;
}
