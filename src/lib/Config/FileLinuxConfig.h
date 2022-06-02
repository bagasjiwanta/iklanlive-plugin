//
// Created by bayus on 02/06/22.
//

#ifdef __linux__

#ifndef IKLANLIVE_PLUGIN_FILELINUXCONFIG_H
#define IKLANLIVE_PLUGIN_FILELINUXCONFIG_H

#include "./FilePluginConfig.h"

class FileLinuxConfig: public FilePluginConfig {
public:
  config_t* open_config();
};


#endif //IKLANLIVE_PLUGIN_FILELINUXCONFIG_H
#endif // __linux__