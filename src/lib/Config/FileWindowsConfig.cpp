//
// Created by bayusamudra on 6/3/2022.
//

#include "FileWindowsConfig.h"
#include <cstdlib>
#include <ShlObj.h>
#include <string>
#include <fileapi.h>
using namespace std;

static string get_appdata()
{
	PWSTR appdata = nullptr;
	if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE,
				 nullptr, &appdata) == S_OK) {
		size_t charsConverted;

		char dest[MAX_PATH * 2 + 1];
		wcstombs_s(&charsConverted, dest, MAX_PATH * 2 + 1, appdata,
			   MAX_PATH);

		std::string appdata_path = string(dest);

		return appdata_path;
	} else {
		blog(LOG_WARNING, "Failed to get %appdata% path");
		return "";
	}
}

static bool is_directory_exist(string path) {
	DWORD attr = GetFileAttributesA(path.c_str());

	return attr != INVALID_FILE_ATTRIBUTES &&
	       !!(attr & FILE_ATTRIBUTE_DIRECTORY);
}

config_t *FileWindowsConfig::open_config(){
	if(this->config) {
		return this->config;
	}else{
		string config_dir = get_appdata() + "\\iklanlive";
		if(!is_directory_exist(config_dir)) {
			int result = CreateDirectoryA(config_dir.c_str(), nullptr);
			if(!result) {
				blog(LOG_ERROR, "Failed to create iklanlive folder");
				return nullptr;
			}
		}

		config_dir += "\\iklanlive.conf";
		int result = config_open(&this->config, config_dir.c_str(), CONFIG_OPEN_EXISTING);

		if(result == CONFIG_FILENOTFOUND) {
			blog(LOG_INFO, "Config at %s is not available. Creating the new one.", config_dir.c_str());
			this->config = config_create(config_dir.c_str());
		}

		this->path = config_dir;
		return this->config;
	}
}