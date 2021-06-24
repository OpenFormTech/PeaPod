#ifndef FloatSensor_H
#define FloatSensor_H

#include "Arduino.h"
#include "Sensor.h"

class FloatSensor : public Sensor {
    public:
        FloatSensor(uint8_t pin);
    private:
        float read() override;
        bool init() override;
        /**
         * Digital input pin.
         * */
        uint8_t pin;
};


#endif