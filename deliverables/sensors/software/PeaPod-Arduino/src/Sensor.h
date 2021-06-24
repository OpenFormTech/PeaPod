#ifndef Sensor_H
#define Sensor_H

#include "Arduino.h"

class Sensor{
  private:
    //The minimum time (in ms) between sensor reads.
    uint16_t delta;
    //The last time the sensor was read, ms since program start.
    unsigned long lastread;
  protected:
    virtual float read() = 0;
    virtual bool init() = 0;
    //Has begin() been performed by THIS object?
    bool ready = false;
    float cachedread;
  public:
    /**
     * Hardware ID.
    */
    String id;
    /**
     * Meaningful, readable name of the sensor.
    */
    String name;
    /**
     * Preformatted (lowercase and underscored) name of the environment variable the sensor records.
    */
    String evname;
    Sensor(String name, String id, String evname, uint16_t delta);
    //Calls read() and manages delta
    float getRead();
    //Sets ready in accordance with init()
    bool begin();
};

#endif