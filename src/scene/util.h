//
// Created by bayus on 26/05/22.
//

#ifndef IKLANLIVE_PLUGIN_UTIL_H
#define IKLANLIVE_PLUGIN_UTIL_H

#include <obs-module.h>
#include "./types.h"

const char *get_url_string(uint32_t id);
obs_source_t *create_browser_source(const char *link);
void update_browser_source(obs_source_t *source, const char *link);
livestream_session getClosestLivestream();
bool isLivestreamStarted(int livestreamId);
bool isTimestampPassed(time_t t);
std::string str_tolower(std::string s);
bool compare_start_ts(livestream_session s1, livestream_session s2);

#endif //IKLANLIVE_PLUGIN_UTIL_H
