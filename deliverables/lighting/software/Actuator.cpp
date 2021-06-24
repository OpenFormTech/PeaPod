#include "Arduino.h"
#include "Actuator.h"

/**
 * Constructor. 
 * @param name - Meaningful, readable name of the actuator.
 * @param id - Identifying name of the associated hardware.
 * @param evname - Name of the environment variable the actuator changes.
 **/
Actuator::Actuator(String name, String id, String evname){
    this->id = id;
    this->name = name;
    this->evname = evname;
    //just in case
    this->evname.toLowerCase();
    this->evname.replace(' ','-');
}

void Actuator::updateActuator(){
    if(this->ready){
        this->update();
    }
}

bool Actuator::begin(){
    this->ready = init();
    return ready;
}