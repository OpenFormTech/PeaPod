#include "SHT31.h"

/**
 * One constructor, begin, and error checks all in one! solid.
 * Assumes serial is ready.
 * */
SHT31::SHT31(TwoWire *wire){
  _wire = wire;
  humidity = NAN;
  temp = NAN;
}

bool SHT31::begin(uint8_t i2caddr){
  _wire->begin();
  _i2caddr = i2caddr;
  reset();
  begun = (readStatus() != 0xFFFF);
  return begun;
}

uint16_t SHT31::readStatus(void) {
  writeCommand(SHT31_READSTATUS);
  _wire->requestFrom(_i2caddr, (uint8_t)3);
  uint16_t stat = _wire->read();
  stat <<= 8;
  stat |= _wire->read();
  // Serial.println(stat, HEX);
  return stat;
}

void SHT31::reset(void) {
  writeCommand(SHT31_SOFTRESET);
  delay(10);
}

void SHT31::heater(bool h) {
  if (h)
    writeCommand(SHT31_HEATEREN);
  else
    writeCommand(SHT31_HEATERDIS);
  delay(1);
}

/*!
 *  @brief  Return sensor heater state
 *  @return heater state (TRUE = enabled, FALSE = disabled)
 */
bool SHT31::isHeaterEnabled() {
  uint16_t regValue = readStatus();
  return (bool)bitRead(regValue, SHT31_REG_HEATER_BIT);
}

float SHT31::readTemperature(void) {
  if (!readTempHum()){
    return NAN;
  }
  return temp;
}

float SHT31::readHumidity(void) {
  if (!readTempHum()){
    return NAN;
  }
  return humidity;
}

/**
 * Performs a CRC8 calculation on the supplied values.
 *
 * @param data  Pointer to the data to use when calculating the CRC8.
 * @param len   The number of bytes in 'data'.
 *
 * @return The computed CRC8 value.
 */
static uint8_t crc8(const uint8_t *data, int len) {
  /*
   *
   * CRC-8 formula from page 14 of SHT spec pdf
   *
   * Test data 0xBE, 0xEF should yield 0x92
   *
   * Initialization data 0xFF
   * Polynomial 0x31 (x8 + x5 +x4 +1)
   * Final XOR 0x00
   */

  const uint8_t POLYNOMIAL(0x31);
  uint8_t crc(0xFF);

  for (int j = len; j; --j) {
    crc ^= *data++;

    for (int i = 8; i; --i) {
      crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
    }
  }
  return crc;
}

bool SHT31::readTempHum(void) {
  uint8_t readbuffer[6];

  writeCommand(SHT31_MEAS_HIGHREP);

  delay(20);
  _wire->requestFrom(_i2caddr, sizeof(readbuffer));
  if (_wire->available() != sizeof(readbuffer))
    return false;
  for (size_t i = 0; i < sizeof(readbuffer); i++) {
    readbuffer[i] = _wire->read();
  }

  if (readbuffer[2] != crc8(readbuffer, 2) ||
      readbuffer[5] != crc8(readbuffer + 3, 2))
    return false;

  int32_t stemp = (int32_t)(((uint32_t)readbuffer[0] << 8) | readbuffer[1]);
  // simplified (65536 instead of 65535) integer version of:
  // temp = (stemp * 175.0f) / 65535.0f - 45.0f;
  stemp = ((4375 * stemp) >> 14) - 4500;
  temp = (float)stemp / 100.0f;

  uint32_t shum = ((uint32_t)readbuffer[3] << 8) | readbuffer[4];
  // simplified (65536 instead of 65535) integer version of:
  // humidity = (shum * 100.0f) / 65535.0f;
  shum = (625 * shum) >> 12;
  humidity = (float)shum / 100.0f;

  return true;
}

void SHT31::writeCommand(uint16_t cmd) {
  _wire->beginTransmission(_i2caddr);
  _wire->write(cmd >> 8);
  _wire->write(cmd & 0xFF);
  _wire->endTransmission();
}

bool SHT31::hasBegun(){
  return begun;
}

//Yatta yatta

SHT31_temp::SHT31_temp(SHT31 *sensor) : Sensor("Temperature Sensor", "SHT31", "Air Temperature", 1000){
  this->sensor = sensor;
}

float SHT31_temp::read(){
  return sensor->readTemperature();
}

bool SHT31_temp::init(){
  return sensor->hasBegun() || sensor->begin();
}

SHT31_hum::SHT31_hum(SHT31 *sensor) : Sensor("Humidity Sensor", "SHT31", "Air Humidity", 1000){
  this->sensor = sensor;
}

float SHT31_hum::read(){
  return sensor->readHumidity();
}

bool SHT31_hum::init(){
  return sensor->hasBegun() || sensor->begin();
}