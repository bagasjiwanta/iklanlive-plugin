//
// Created by bayus on 07/05/22.
//

#include "AuthException.h"

std::string AuthException::to_string() {
  if(this->error == CREDENTIAL_MISMATCH){
    return "Username or password is incorrect";
  }else{
    return this->message;
  }
}

AuthException::AuthException(auth_error_type error, std::string message) : error(error), message(message) {}

auth_error_type AuthException::getError() const {
  return error;
}
