#include "Scale.h"
#include "NAU7802.h"

Scale::Scale() : Sensor("Scale", "NAU7802", "mass", 3){
    //Look up the calibration factor in EEPROM?
}

bool Scale::init(){
    return (nau7802.begin());
}

//if readings < avg readings: total += reading (checks available), readings++, return NAN
//else calculate average reading, reset readings and total, return avg converted to weight

float Scale::read(){

    if(!nau7802.available()){
        return NAN;
        // Serial.println("NAU7802 not available!");
    }
    
    //Non-intrusive average
    if(i < AVG_READINGS){
        total += nau7802.getReading();
        i++;
        return NAN;
    }

    double result = (total/AVG_READINGS-nau7802.getZeroOffset())/(nau7802.getCalibrationFactor());
    restart();

    return (float)result;
}

void Scale::calibrate(float grams){
    if(grams == 0.0){
        nau7802.calculateZeroOffset(CALIBRATION_READINGS);
    } else {
        nau7802.calculateCalibrationFactor(grams, CALIBRATION_READINGS);
    }
    restart();
}

void Scale::restart(){
    i = 0;
    total = 0;
}