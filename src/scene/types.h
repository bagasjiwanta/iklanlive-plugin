//
// Created by bayus on 26/05/22.
//

#ifndef IKLANLIVE_PLUGIN_TYPES_H
#define IKLANLIVE_PLUGIN_TYPES_H

#include <obs-module.h>

using namespace std;

struct ads {
  const char* url;
  obs_source_t *source;
  uint32_t stream_id;
};

#endif //IKLANLIVE_PLUGIN_TYPES_H
