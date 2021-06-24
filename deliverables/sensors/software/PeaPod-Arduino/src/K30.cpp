#include "Arduino.h"
#include "K30.h" 
#include "Wire.h"


K30::K30(TwoWire *wire, uint16_t i2c_address) : Sensor("CO2 Sensor", "K30", "ppm CO2", 2000) {
  this->wire = wire;
  _i2c_address = i2c_address;
}

bool K30::init(){
  wire->begin();
  return true;
}

float K30::read()
{
  byte recValue[4] = {0,0,0,0};

  wire->beginTransmission(_i2c_address);
  wire->write(0x22);
  wire->write(0x00);
  wire->write(0x08);
  wire->write(0x2A);
  wire->endTransmission();
  delay(30); 
  

  wire->requestFrom(_i2c_address,4);
  delay(20);
   
  byte i=0;
  while(wire->available())
  {
    recValue[i] = wire->read();
    i++;
  }
  
  byte checkSum = recValue[0] + recValue[1] + recValue[2];
  
  if (checkSum == recValue[3]){
    return (recValue[1] << 8) + recValue[2];
  } 
  return NAN;
}
