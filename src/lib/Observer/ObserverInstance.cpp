//
// Created by bayus on 07/05/22.
//

#include "ObserverInstance.h"

static Observer::Observer* obj = nullptr;

Observer::Observer *Observer::get_observer() {
  if(!obj){
    obj = new Observer;
  }

  return obj;
}

void Observer::free_observer() {
  if(obj) delete obj;
}
