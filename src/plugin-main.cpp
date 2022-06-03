/*
Plugin Iklanlive
Copyright (C) 2022 Inkubator IT

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

// #define _HAS_STD_BYTE 0
#include <obs-module.h>
#include "plugin-config.h"
#include "plugin-macros.generated.h"
#include "component/Menu.h"
#include <obs-frontend-api.h>
#include "lib/Observer/ObserverInstance.h"
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <string>
#include "./dialog/LoginDialog.h"
#include "./scene/ads_scene.h"

using json = nlohmann::json;

static void source_register();

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

Config::PluginConfig config;

bool obs_module_load(void){
  Q_INIT_RESOURCE(iklanlive);

  config.load_config();

  load_menu((QMainWindow*) obs_frontend_get_main_window());

  source_register();

  blog(LOG_INFO, "%s says : iklanlive plugin loaded successfully (version %s)",
       PLUGIN_VERSION);

  return true;
}

void obs_module_unload()
{
    config.close_config();
    Observer::free_observer();

  blog(LOG_INFO, "plugin unloaded");
}

static void source_register() {
	blog(LOG_INFO, "Registering source %s...", ads_info.get_name(nullptr));
	obs_register_source(&ads_info);
	blog(LOG_INFO, "Source Registered");
}