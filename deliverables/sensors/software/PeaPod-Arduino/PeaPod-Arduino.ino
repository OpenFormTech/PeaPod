#include "SHT31.h"
#include "Sensor.h"
#include "Wire.h"
#include "K30.h"
#include "FloatSensor.h"
#include "Scale.h"
// #include "LED.h"
// #include "Actuator.h"

//MACRO DEFINITIONS
#define NUM_SENSORS 5
#define FLOATSENSOR_PIN 5
// #define NUM_ACTUATORS 1
// #define LED_PIN 4
#define REVISION 0

// Sensors
SHT31 sht31;
SHT31_temp temp = SHT31_temp(&sht31);
SHT31_hum hum = SHT31_hum(&sht31);
K30 k30;
Scale scale;
FloatSensor fs = FloatSensor(FLOATSENSOR_PIN);

// Actuators
// LED led(LED_PIN);

Sensor *sensors [NUM_SENSORS] = {
    &temp,
    &hum,
    &k30,
    &fs,
    &scale
};

// Actuator* actuators [NUM_ACTUATORS] = {
//     &led
// };

void setup()
{
    digitalWrite(13, LOW);
    if(!post()){
        // Failed POST
        while(true){
            delay(250);
            digitalWrite(13, HIGH);
            delay(250);
            digitalWrite(13, LOW);
        }
    }

    // Tell computer 'ready', wait to receive valid program.
    Serial.println(0);

    String ins;
    do{
        while(!Serial.available());
        ins = Serial.readString();
        ins.trim();
    }while(!handleInstructions(ins));
    digitalWrite(13, HIGH);
}

void loop()
{
    if(Serial.available()){
        String in = Serial.readString();
        in.trim(); //Whitespace or newlines
        handleInstructions(in);
    }

    for(int i = 0; i < NUM_SENSORS; i++){
        float read = sensors[i]->getRead();
        if(!isnan(read)){
            Serial.print("{\"type\":\"data\",\"msg\":{\"label\":\"");
            Serial.print(sensors[i]->evname);
            Serial.print("\",\"value\":");
            Serial.print(read);
            Serial.println("}}");
        }
    }

    // for(int i = 0; i < NUM_ACTUATORS; i++){
    //     actuators[i]->updateActuator();
    // }
    delay(10);
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
        if(var.equals("scale")){
            scale.calibrate(value);
            return true;
        }
        // for(int i = 0; i < NUM_ACTUATORS; i++){
        //     if(var.equals(actuators[i]->evname)){
        //         Serial.print("{\"type\":\"debug\",\"msg\":\"Actuator '");
        //         Serial.print(actuators[i]->name);
        //         Serial.print("' target set to ");
        //         Serial.print(value);
        //         Serial.println(".\"}");
        //         actuators[i]->target = value;
        //         return true;
        //     }
        // }

        Serial.print("{\"type\":\"error\",\"msg\":\"Unknown target '");
        Serial.print(var);
        Serial.println("'\"}");
        return false;
    }
    Serial.print("{\"type\":\"error\",\"msg\":\"Failed to handle instruction '");
    in.replace("\"", "\\\"");
    Serial.print(in);
    Serial.println("'\"}");
    return false;
}

/**
 * Handles incoming instruction dictionary {"var":val,...}
 * Continues regardless of failure of a single instruction, alerts only
 * @param s - Instructions dictionary string
 * @return were all instructions handled in a valid way?
 * */
bool handleInstructions(String ins){
    if(ins.equals("{}")){
        return true;  //Empty dictionary, by default handled
    }
    if(ins.charAt(0) != '{' || ins.charAt(ins.length()-1) != '}'){
        Serial.print("{\"type\":\"error\",\"msg\":\"Invalid instructions dictionary '");
        Serial.print(ins);
        Serial.println("'\"}");
        return false;
    }
    ins = ins.substring(1, ins.length()-1); //Strips surrounding {}

    //Handles each individual instruction

    bool result = true;
    //While there are multiple instructions
    while(ins.indexOf(',') != -1){
        //Did the leftmost one succeed?
        result &= handleInstruction(ins.substring(0, ins.indexOf(',')));
        //Truncate leftmost instruction
        ins = ins.substring(ins.indexOf(',')+1);
    }
    //Handle last/only instruction (there are no commas left)
    result &= handleInstruction(ins);
    return result;
}

bool post(){
    Serial.begin(9600);
    while(!Serial); //Waits until serial opens

    // Test Serial protocol: send software revision byte, recieve check (0) byte or stop (!0) byte
    Serial.println(REVISION);
    while(!Serial.available());
    if(Serial.parseInt() != 0){
        return false;
    }

    // Test sensor protocols - per-sensor tests
    bool success = true;
    for(int i = 0; i < NUM_SENSORS; i++){
        bool latest = sensors[i]->begin();
        success &= latest;
        if(!latest){
            Serial.print("{\"type\":\"error\",\"msg\":\"Failed to initialize sensor '");
            Serial.print(sensors[i]->name);
            Serial.println("'. Check wiring.\"}");
        } else {
            Serial.print("{\"type\":\"debug\",\"msg\":\"Sensor '");
            Serial.print(sensors[i]->name);
            Serial.println("' initialized successfully.\"}");
        }
    }

    // for(int i = 0; i < NUM_ACTUATORS; i++){
    //     bool latest = actuators[i]->begin();
    //     success &= latest;
    //     if(!latest){
    //         Serial.print("{\"type\":\"error\",\"msg\":\"Failed to initialize actuator '");
    //         Serial.print(actuators[i]->name);
    //         Serial.println("'. Check wiring.\"}");
    //     } else {
    //         Serial.print("{\"type\":\"debug\",\"msg\":\"Actuator '");
    //         Serial.print(actuators[i]->name);
    //         Serial.println("' initialized successfully.\"}");
    //     }
    // }
    return success;
}
