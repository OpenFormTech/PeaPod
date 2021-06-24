#ifndef LED_H
#define LED_H

#include "Actuator.h"

#define LED_BRIGHTNESS_FACTOR 0.1

enum t_color { LED_N, LED_BLUE, LED_COOL, LED_WARM, LED_RED, LED_FAR };

class LED : public Actuator {
    public:
        LED(uint8_t pin, t_color color);
        LED(uint8_t pin);
    private:
        void update() override;
        bool init() override;
        /**
         * PWM output pin.
         * */
        uint8_t pin;
};

#endif