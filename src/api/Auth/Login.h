//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_LOGIN_H
#define IKLANLIVE_PLUGIN_LOGIN_H

#include "./User.h"
#include <string>

using namespace std;

namespace Auth{
  User login(const string& email, const string& password);
};

#endif //IKLANLIVE_PLUGIN_LOGIN_H
