#include "Arduino.h"
#include "Sensor.h"

/**
 * Constructor. 
 * @param _name - Meaningful, readable name of the sensor.
 * @param _id - Identifying name of the associated hardware.
 * @param _evname - Name of the environment variable the sensor records.
 * @param _delta - The minimum time (in ms) between sensor reads.
 * @param __read - Pointer to the hardware-level read function.
 * @param _args - Pointer to static arguments to pass to hardware-level read function.
 **/
Sensor::Sensor(String name, String id, String evname, uint16_t delta){
    this->id = id;
    this->name = name;
    this->evname = evname;
    //just in case
    this->evname.toLowerCase();
    this->evname.replace(' ','-');
    this->delta = delta;
    //Buffer - Resets the last read time to the current time
    lastread = millis();
}

/**
 * Wrapper for hardware-level read function. Checks that enough time has passed between reads, and checks for `ready` flag and types. 
 * @return Sensor read, or nan. Usually nan. Like 99% of the time nan.
 **/
float Sensor::getRead(){
    float result = NAN;
    //Has enough time passed between reads?
    if(ready && millis()-lastread > delta){
        result = read();
        //Reset the last read time to now
        //BUFFER - Happens post-read
        lastread = millis();
        cachedread = result;
    }
    return result;
}

bool Sensor::begin(){
    ready = init();
    return ready;
}