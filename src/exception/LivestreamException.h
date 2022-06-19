#ifndef IKLANLIVE_PLUGIN_LIVESTREAMEXCEPTION_H
#define IKLANLIVE_PLUGIN_LIVESTREAMEXCEPTION_H

#include "BaseException.h"
#include <string>

enum livestream_error_type {
	BAD_REQUEST,
	PARSE_ERROR,
	INVALID_FORMAT,
	UNKNOWN_LIVESTREAM_ERROR,
	NO_AVAILABLE_LIVESTREAM
};

class LivestreamException : public BaseException {
	livestream_error_type error;
	std::string message;

public:
	LivestreamException(livestream_error_type error, std::string message);

	std::string to_string() override;

	livestream_error_type getError() const;
};

#endif // IKLANLIVE_PLUGIN_LIVESTREAMEXCEPTION_H