//
// Created by bayus on 07/05/22.
//

#include "Observer.h"

void Observer::Observer::subscribe(string event, function<void(void*)> func) {
  if(!this->db.count(event)){
    // Key is not found. Create the new one
    this->db[event] = vector<function<void(void*)>>();
  }

  this->db[event].push_back(func);
}

void Observer::Observer::notify(string event, void *payload) {
  if(!this->db.count(event)){
    return;
  }

  for(auto i: this->db[event]){
    i(payload);
  }
}
