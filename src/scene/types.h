//
// Created by bayus on 26/05/22.
//

#ifndef IKLANLIVE_PLUGIN_TYPES_H
#define IKLANLIVE_PLUGIN_TYPES_H

#include <obs-module.h>
#include <string>
#include <time.h>

struct ads {
	const char *url;
	obs_source_t *source, *main_source;
	uint32_t stream_id;
};

struct livestream_session {
	std::string name = "";
	int stream_id = -1;
	time_t utc_start_timestamp = NULL;
	std::string status = "";
};

#endif //IKLANLIVE_PLUGIN_TYPES_H
