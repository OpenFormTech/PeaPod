#include "LED.h"

String parseEnum(t_color color);

LED::LED(uint8_t pin, t_color color) : Actuator(parseEnum(color), "led-"+String(pin), "lighting"){
    this->pin = pin;
}

String parseEnum(t_color color){
    switch(color){
        case LED_BLUE:
            return "Royal Blue LEDs";
        case LED_COOL:
            return "Cool White LEDs";
        case LED_WARM:
            return "Warm White LEDs";
        case LED_RED:
            return "Photo Red LEDs";
        case LED_FAR:
            return "Far Red LEDs";
        default:
            return "LEDs";
    }
}

bool LED::init(){
    this->target = 0;
    pinMode(this->pin, OUTPUT);
    return true;
}

void LED::update(){
    // Clamp to 0<x<1
    this->target = clamp(target, 0, 1);
    float power = this->target*255*LED_BRIGHTNESS_FACTOR;
    Serial.print("Power: ");
    Serial.println(power);
    analogWrite(this->pin, power);
}