//
// Created by bayus on 26/05/22.
//

#ifndef IKLANLIVE_PLUGIN_UTIL_H
#define IKLANLIVE_PLUGIN_UTIL_H

#include <obs-module.h>

const char* get_url_string(uint32_t id);
obs_source_t* create_browser_source(const char* link);
void update_browser_source(obs_source_t *source, const char* link);

#endif //IKLANLIVE_PLUGIN_UTIL_H
