//
// Created by bayus on 02/06/22.
//

#ifdef __linux__

#include "FileLinuxConfig.h"
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <string>

using namespace std;

config_t *FileLinuxConfig::open_config() {
  if (this->config) {
    return this->config;
  }else{
    struct passwd *pw = getpwuid(getuid());
    const char* ch =  pw->pw_dir;

    string config_dir = string(ch) + "/.config";

    struct stat buffer;
    if(stat(config_dir.c_str(), &buffer) != 0){
      mkdir(config_dir.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    config_dir += "/iklanlive";
    if(stat(config_dir.c_str(), &buffer) != 0){
      mkdir(config_dir.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    config_dir += "/iklanlive.conf";
    int result = config_open(&this->config, config_dir.c_str(), CONFIG_OPEN_EXISTING);

    if(result == CONFIG_FILENOTFOUND) {
      blog(LOG_INFO, "Config at %s is not available. Creating the new one.", config_dir.c_str());
      this->config = config_create(config_dir.c_str());
    }

    this->path = config_dir;
    return this->config;
  }
}

#endif // __linux__