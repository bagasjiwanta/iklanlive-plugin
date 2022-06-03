//
// Created by bayus on 26/05/22.
//

#include "util.h"

const char* get_url_string(uint32_t id) {
  char* res = (char*) "https://www.google.com";
  return res;
}

obs_source_t* create_browser_source(const char* link) {
  blog(LOG_INFO, "Creating browser source with link %s", link);
  const char* browser = obs_module_text("browser_source");

  blog(LOG_INFO, "Browser id: %s", browser);

  obs_data_t *settings = obs_get_source_defaults(browser);
  obs_source_t *source;

//  obs_data_set_int(settings, "color", 0xF47C7Cff);
//  obs_data_set_string(settings, "file", "/home/bayus/Pictures/bikinibottom.jpg");
  source = obs_source_create_private(browser, nullptr, settings);

  obs_data_release(settings);

  blog(LOG_INFO, "Browser source created successfully");

  return source;
}

void update_browser_source(obs_source_t *source, const char* link) {
  obs_data_t *settings = obs_data_create();

  obs_data_set_string(settings, "url", link);
  obs_source_update(source, settings);

  obs_data_release(settings);
}