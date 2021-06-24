#ifndef SHT31_H
#define SHT31_H

#include "Arduino.h"
#include "Sensor.h"
#include "Wire.h"

#define SHT31_DEFAULT_ADDR 0x44 /**< SHT31 Default Address */
#define SHT31_MEAS_HIGHREP_STRETCH                                             \
  0x2C06 /**< Measurement High Repeatability with Clock Stretch Enabled */
#define SHT31_MEAS_MEDREP_STRETCH                                              \
  0x2C0D /**< Measurement Medium Repeatability with Clock Stretch Enabled */
#define SHT31_MEAS_LOWREP_STRETCH                                              \
  0x2C10 /**< Measurement Low Repeatability with Clock Stretch Enabled*/
#define SHT31_MEAS_HIGHREP                                                     \
  0x2400 /**< Measurement High Repeatability with Clock Stretch Disabled */
#define SHT31_MEAS_MEDREP                                                      \
  0x240B /**< Measurement Medium Repeatability with Clock Stretch Disabled */
#define SHT31_MEAS_LOWREP                                                      \
  0x2416 /**< Measurement Low Repeatability with Clock Stretch Disabled */
#define SHT31_READSTATUS 0xF32D   /**< Read Out of Status Register */
#define SHT31_CLEARSTATUS 0x3041  /**< Clear Status */
#define SHT31_SOFTRESET 0x30A2    /**< Soft Reset */
#define SHT31_HEATEREN 0x306D     /**< Heater Enable */
#define SHT31_HEATERDIS 0x3066    /**< Heater Disable */
#define SHT31_REG_HEATER_BIT 0x0d /**< Status Register Heater Bit */

extern TwoWire Wire; /**< Forward declarations of Wire for board/variant
                        combinations that don't have a default 'Wire' */

/**
 * Driver for the Adafruit SHT31-D Temperature and Humidity breakout board.
 */
class SHT31 {
public:
  /**
   *  Constructor.
   */
  SHT31(TwoWire *theWire = &Wire);

  bool begin(uint8_t i2caddr = SHT31_DEFAULT_ADDR);

  /**
   * Gets a single temperature reading from the sensor.
   *
   * @return A float value indicating the temperature.
   */
  float readTemperature(void);

  /**
   * Gets a single relative humidity reading from the sensor.
   *
   * @return A float value representing relative humidity.
   */
  float readHumidity(void);

  /**
   * Gets the current status register contents.
   *
   * @return The 16-bit status register.
   */
  uint16_t readStatus(void);

  /**
   * Performs a reset of the sensor to put it into a known state.
   */
  void reset(void);

  /**
   * Enables or disabled the heating element.
   *
   * @param h True to enable the heater, False to disable it.
   */
  void heater(bool h);

  /**
   * Gets the current status register heater bit.
   *
   * @return Boolean value, True = enabled, False = disabled.
   */
  bool isHeaterEnabled();

  TwoWire *_wire; /**< Wire object */

  bool hasBegun();

protected:
  bool begun = false;
private:
  /**
   * Placeholder to track humidity internally.
   */
  float humidity;

  /**
   * Placeholder to track temperature internally.
   */
  float temp;

  /**
   * Placeholder to track the I2C address.
   */
  uint8_t _i2caddr;

  /**
   * Internal function to perform a temp + humidity read.
   *
   * @return True if successful, otherwise false.
   */
  bool readTempHum(void);

  /**
   * Internal function to perform and I2C write.
   *
   * @param cmd   The 16-bit command ID to send.
   */
  void writeCommand(uint16_t cmd);

  /**
   * Internal function to read data over the I2C bus.
   *
   * @return True if successful, otherwise False.
   */
  bool readData(void);
};

//WRAPPER CLASSES - Sensor derivatives do define "_read()" using ONE SHT31 object.

class SHT31_temp : public Sensor{
  private:
    SHT31 *sensor;
    float read() override;
    bool init() override;
  public:
    SHT31_temp(SHT31 *sensor);
};

class SHT31_hum : public Sensor{
  private:
    SHT31 *sensor;
    float read() override;
    bool init() override;
  public:
    SHT31_hum(SHT31 *sensor);
};

#endif
