#ifndef K30_h
#define K30_h

#include "Arduino.h"
#include "Wire.h"
#include "Sensor.h"

#define K30_DEFAULT_ADDR 0x68

extern TwoWire Wire;

class K30 : public Sensor
{
  public:
    K30(TwoWire *wire = &Wire, uint16_t i2c_address = K30_DEFAULT_ADDR);
  private:
    float read() override;
    bool init() override;
    int _i2c_address;
    TwoWire *wire;
};
#endif
