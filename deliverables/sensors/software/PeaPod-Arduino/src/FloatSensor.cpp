#include "FloatSensor.h"

FloatSensor::FloatSensor(uint8_t pin) : Sensor("Float Sensor", "Float Switch", "Reservoir Level", 500){
    this->pin = pin;
}

bool FloatSensor::init(){
    pinMode(pin, INPUT);
    return true;
}

float FloatSensor::read(){
    return digitalRead(pin);
}