//
// Created by bayus on 26/05/22.
//

#include "util.h"

const char* get_url_string(uint32_t id) {
  char* res = "https://www.google.com";
  return res;
}

obs_source_t* create_browser_source(const char* link) {
  obs_data_t *settings = obs_data_create();
  obs_source_t *source;

  obs_data_set_string(settings, "url", link);

  source = obs_source_create_private("browser_source", NULL, settings);

  obs_data_release(settings);

  return source;
}

void update_browser_source(obs_source_t *source, const char* link) {
  obs_data_t *settings = obs_data_create();

  obs_data_set_string(settings, "url", link);
  obs_source_update(source, settings);

  obs_data_release(settings);
}