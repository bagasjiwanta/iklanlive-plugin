//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_OBSERVERINSTANCE_H
#define IKLANLIVE_PLUGIN_OBSERVERINSTANCE_H

#include "Observer.h"

namespace Observer {
  Observer* get_observer();
  void free_observer();
};


#endif //IKLANLIVE_PLUGIN_OBSERVERINSTANCE_H
