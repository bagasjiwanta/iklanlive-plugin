//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_AUTHEXCEPTION_H
#define IKLANLIVE_PLUGIN_AUTHEXCEPTION_H

#include "BaseException.h"

enum auth_error_type {
  CREDENTIAL_MISMATCH,
  INPUT_NOT_COMPLETE,
  UNKNOWN
};

class AuthException: public BaseException {
  auth_error_type error;
  std::string message;

public:
  AuthException(auth_error_type error, std::string message);

  std::string to_string() override;

  auth_error_type getError() const;

};


#endif //IKLANLIVE_PLUGIN_AUTHEXCEPTION_H
