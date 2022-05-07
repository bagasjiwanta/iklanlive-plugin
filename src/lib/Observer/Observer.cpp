//
// Created by bayus on 07/05/22.
//

#include "Observer.h"
#include <string>
#include <functional>
#include <vector>
void Observer::Observer::subscribe(std::string event, std::function<void(void*)> func) {
  if(!this->db.count(event)){
    // Key is not found. Create the new one
    this->db[event] = std::vector<std::function<void(void*)>>();
  }

  this->db[event].push_back(func);
}

void Observer::Observer::notify(std::string event, void *payload) {
  if(!this->db.count(event)){
    return;
  }

  for(auto i: this->db[event]){
    i(payload);
  }
}
