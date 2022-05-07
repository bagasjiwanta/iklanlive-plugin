//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_BASEEXCEPTION_H
#define IKLANLIVE_PLUGIN_BASEEXCEPTION_H

#include <string>
using namespace std;

class BaseException {
public:
  virtual string to_string() = 0;
};


#endif //IKLANLIVE_PLUGIN_BASEEXCEPTION_H
