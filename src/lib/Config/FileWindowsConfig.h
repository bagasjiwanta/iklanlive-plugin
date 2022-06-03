//
// Created by bayusamudra on 6/3/2022.
//

#ifdef _WIN32

#ifndef IKLANLIVE_PLUGIN_FILEWINDOWSCONFIG_H
#define IKLANLIVE_PLUGIN_FILEWINDOWSCONFIG_H

#include "./FilePluginConfig.h"

class FileWindowsConfig: public FilePluginConfig {
public:
	config_t* open_config();
};


#endif //IKLANLIVE_PLUGIN_FILEWINDOWSCONFIG_H

#endif