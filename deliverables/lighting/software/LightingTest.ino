#include "LED.h"
#include "Actuator.h"

#define NUM_ACTUATORS 5
#define LED_PIN_BLUE 3
#define LED_PIN_COOL 5
#define LED_PIN_WARM 6
#define LED_PIN_RED 9
#define LED_PIN_FAR 10

LED ledBlue(LED_PIN_BLUE, LED_);
LED ledCool(LED_PIN_COOL);
LED ledWarm(LED_PIN_WARM);
LED ledRed(LED_PIN_RED);
LED ledFar(LED_PIN_FAR);

Actuator* actuators [NUM_ACTUATORS] = {
    &ledBlue,
    &ledCool,
    &ledWarm,
    &ledRed,
    &ledFar,
};

void setup(){
    Serial.begin(9600);
    while(!Serial);

    bool success = true;
    for(int i = 0; i < NUM_ACTUATORS; i++){
        bool latest = actuators[i]->begin();
        success &= latest;
        if(!latest){
            Serial.print("{\"type\":\"error\",\"msg\":\"Failed to initialize actuator '");
            Serial.print(actuators[i]->name);
            Serial.println("'. Check wiring.\"}");
        } else {
            Serial.print("{\"type\":\"debug\",\"msg\":\"Actuator '");
            Serial.print(actuators[i]->name);
            Serial.println("' initialized successfully.\"}");
        }
    }
}

void loop(){
    if(Serial.available()){
        String ins = Serial.readString();
        ins.trim(); //Whitespace or newlines
        if(!ins.equals("{}") && ins.charAt(0) == '{' && ins.charAt(ins.length()-1) == '}'){
            ins = ins.substring(1, ins.length()-1); //Strips surrounding {}
            //While there are multiple instructions
            while(ins.indexOf(',') != -1){
                //Did the leftmost one succeed?
                handleInstruction(ins.substring(0, ins.indexOf(',')));
                //Truncate leftmost instruction
                ins = ins.substring(ins.indexOf(',')+1);
            }
            //Handle last/only instruction (there are no commas left)
            handleInstruction(ins);
        }
    }
}

/**
 * Handles incoming instruction "var":value string.
 * @param s - Instruction string
 * @return was the instruction handled in a valid way?
 **/
bool handleInstruction(String in){
    uint8_t split = in.indexOf(":");
    if(split!=-1 && in.charAt(0) == '"' && in.charAt(split-1) == '"'){
        String var = in.substring(1, split-1); //Assumes surrounding ""
        float value = in.substring(split+1).toFloat();

        //INSTRUCTION HANDLING IF BLOCKS - EACH RETURNS TRUE
        for(int i = 0; i < NUM_ACTUATORS; i++){
            if(var.equals(actuators[i]->evname)){
                Serial.print("{\"type\":\"debug\",\"msg\":\"Actuator '");
                Serial.print(actuators[i]->name);
                Serial.print("' target set to ");
                Serial.print(value);
                Serial.println(".\"}");
                actuators[i]->target = value;
                return true;
            }
        }
    }
}