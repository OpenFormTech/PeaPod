#include "LED.h"

LED::LED(uint8_t pin) : Actuator("LED", "led0", "led"){
    this->pin = pin;
}

bool LED::init(){
    this->target = 0;
    pinMode(this->pin, OUTPUT);
    return true;
}

void LED::update(){
    // Clamp to 0<x<1
    this->target = min(max(target, 0), 1);
    Serial.println(this->target*255*LED_BRIGHTNESS_FACTOR);
    analogWrite(this->pin, this->target*255*LED_BRIGHTNESS_FACTOR);
}