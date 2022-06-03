//
// Created by bayus on 07/05/22.
//
#include "plugin-macros.generated.h"
#include "exception/ConfigException.h"
#include "./PluginConfig.h"
#include "./FilePluginConfig.h"
#include "lib/Observer/ObserverInstance.h"
#include <string>
using namespace std;

#ifdef __linux__
  #include "./FileLinuxConfig.h"
  FilePluginConfig* config_file = new FileLinuxConfig();

#elif _WIN32
	#include "./FileWindowsConfig.h"
  FilePluginConfig* config_file = new FileWindowsConfig();
#endif


void Config::PluginConfig::write_config() {
  blog(LOG_INFO, "Start to write config");

  config_t* config = config_file->open_config();

  this->activeUser.to_config(config);

  config_file->save_config();
}

void Config::PluginConfig::load_config() {
  config_t* config = config_file->open_config();

  try{
    blog(LOG_INFO, "Start to load config. Config path : %s", config_file->get_path().c_str());
    this->activeUser.from_config(config);
  }catch(ConfigException* err){
    blog(LOG_ERROR, "Config loading error:\n%s", err->to_string().c_str());
  }

  blog(LOG_INFO, "Config Loading success");

  Observer::get_observer()->notify("update-menu");
}

Auth::User &Config::PluginConfig::getActiveUser() {
  return activeUser;
}
void Config::PluginConfig::close_config() {
	this->write_config();
	config_file->close_config();
}
