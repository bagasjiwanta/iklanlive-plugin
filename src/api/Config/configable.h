//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_CONFIGABLE_H
#define IKLANLIVE_PLUGIN_CONFIGABLE_H

#include <util/config-file.h>

class configable {
public:
  virtual void from_config(const config_t* config) = 0;
  virtual void to_config(config_t* config) = 0;
};


#endif //IKLANLIVE_PLUGIN_CONFIGABLE_H
