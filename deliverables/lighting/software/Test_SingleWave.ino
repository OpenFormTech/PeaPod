#include "Arduino.h"
#include "Actuator.h"
#include "LED.h"

#define LED_PIN 3
#define STEP 0.1

LED led(LED_PIN, LED_BLUE);
float angle = 0;

void setup(){
    Serial.begin(9600);
    while(!Serial);

    if(!led.begin()){
        Serial.println("Failed to initialize. Freezing.");
        while(1){delay(1000);}
    } else {
        Serial.println("Initialized successfully!");
    }
}

void loop(){
    angle += STEP;    //Step the angle
    if(angle > TWO_PI){ angle = 0;}
    Serial.print(angle);
    Serial.println("rad");
    led.target = -cos(angle)/2+0.5;    //Sin wave between 0 and 1
    led.updateActuator();
    delay(100);
}
