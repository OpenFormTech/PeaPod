#ifndef Scale_H
#define Scale_H

#include "Arduino.h"
#include "NAU7802.h"
#include "Sensor.h"

#define AVG_READINGS 320
#define CALIBRATION_READINGS 80

class Scale : public Sensor {
    public:
        Scale();
        void calibrate(float grams);  //Calibrates the scale using a known load (or 0 to tare)
        void restart();
    private:
        bool init() override;
        float read() override;
        NAU7802 nau7802 = NAU7802();  //Default constructed NAU7802 object
        uint16_t i = 0;
        int32_t total = 0;
        // float readings[AVG_READINGS];
};

#endif