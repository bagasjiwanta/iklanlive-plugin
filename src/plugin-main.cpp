/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

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

// powershell -ExecutionPolicy Bypass -File .github/scripts/Build-Windows.ps1
#include <obs-module.h>
#include <cpr/cpr.h>
#include "plugin-macros.generated.h"
#include "component/Menu.h"
#include <obs-frontend-api.h>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

//const char* BACKEND_SERVER = BACKEND_SERVER;

std::string getRandomName () {
	int randomId = rand() % 100 + 1;
	std::string url = "https://rickandmortyapi.com/api/character/" + std::to_string(randomId);
	cpr::Response r = cpr::Get(cpr::Url{url});
	auto j = json::parse(r.text);
	blog(LOG_INFO, "Haha : %s", r.text.c_str());
	return j["name"].get<std::string>();
}

bool obs_module_load(void){
	std::string randomName = getRandomName();
  load_menu((QMainWindow*) obs_frontend_get_main_window());
	blog(LOG_INFO, "%s says : iklanlive plugin loaded successfully (version %s)",
		randomName.c_str(),
	    PLUGIN_VERSION);

	return true;
}

void obs_module_unload()
{
	blog(LOG_INFO, "plugin unloaded");
}
