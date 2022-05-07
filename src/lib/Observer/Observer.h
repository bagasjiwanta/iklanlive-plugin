//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_OBSERVER_H
#define IKLANLIVE_PLUGIN_OBSERVER_H

#include <string>
#include <vector>
#include <map>
using namespace std;

namespace Observer{
  class Observer {
    map<string, vector<void(*)(void*)>> db;
  public:
    void subscribe(string event, void (*func)(void*));
    void notify(string event, void* payload = nullptr);
    void unsubscribe(string event, void (*func)(void*));
  };

}


#endif //IKLANLIVE_PLUGIN_OBSERVER_H
