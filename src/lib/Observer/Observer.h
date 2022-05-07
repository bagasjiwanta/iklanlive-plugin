//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_OBSERVER_H
#define IKLANLIVE_PLUGIN_OBSERVER_H

#include <string>
#include <vector>
#include <map>
#include <functional>
using namespace std;

namespace Observer{
  class Observer {
    map<string, vector<function<void(void*)>>> db;
  public:
    void subscribe(string event, function<void(void*)> func);
    void notify(string event, void* payload = nullptr);
  };

}


#endif //IKLANLIVE_PLUGIN_OBSERVER_H
