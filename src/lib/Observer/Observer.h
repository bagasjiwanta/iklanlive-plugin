//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_OBSERVER_H
#define IKLANLIVE_PLUGIN_OBSERVER_H

#include <string>
#include <vector>
#include <map>
#include <functional>
// using namespace std;

namespace Observer{
  class Observer {
    std::map<std::string, std::vector<std::function<void(void*)>>> db;
  public:
    void subscribe(std::string event, std::function<void(void*)> func);
    void notify(std::string event, void* payload = nullptr);
  };

}


#endif //IKLANLIVE_PLUGIN_OBSERVER_H
