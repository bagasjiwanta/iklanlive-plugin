#include "LivestreamException.h"

LivestreamException::LivestreamException(livestream_error_type error,
					 std::string message)
{
	this->error = error;
	this->message = message;
}

std::string LivestreamException::to_string()
{
	return this->message;
};

livestream_error_type LivestreamException::getError() const
{
	return this->error;
}