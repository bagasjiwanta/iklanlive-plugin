//
// Created by bayus on 03/06/22.
//

#include "./FilePluginConfig.h"

std::string FilePluginConfig::get_path() {
  return this->path;
}

void FilePluginConfig::close_config() {
  if(this->config != nullptr) {
    this->save_config();
    config_close(this->config);
  }
}

void FilePluginConfig::save_config() {
  if(this->config != nullptr) {
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
  }
}