//
// Created by bayus on 07/05/22.
//

#include "Observer.h"

void Observer::Observer::subscribe(string event, void (*func)(void *)) {
  if(!this->db.count(event)){
    // Key is not found. Create the new one
    this->db[event] = vector<void(*)(void*)>();
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

void Observer::Observer::unsubscribe(string event, void (*func)(void *)) {
  if(!this->db.count(event)){
    return;
  }

  vector<void(*)(void*)> filtered;

  for(auto i = this->db[event].begin(); i != this->db[event].end(); i++){
    if(*i != func){
      filtered.push_back(*i);
    }
  }

  this->db[event] = filtered;
}
