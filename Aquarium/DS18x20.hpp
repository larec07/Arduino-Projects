#include "Updatable.hpp"
#include <OneWire.h>
#include "TimeConstants.h"

typedef enum
  {
    DS18x20SensorState_Waiting,
    DS18x20SensorState_PrepareComplete,
  } DS18x20SensorState;

  class DS18x20 : public Updatable {

  public:
    DS18x20(uint8_t pin, unsigned long timeInterval = MINUTE_IN_MILLIS)
    : ds(OneWire(pin)), updateInterval(timeInterval), lastUpdatedTime(0), state(DS18x20SensorState_Waiting) {};

  public:
    void Update (unsigned long currentTime) {

      if (state == DS18x20SensorState_Waiting && abs(currentTime - lastUpdatedTime) <= updateInterval) {

        lastUpdatedTime = currentTime;
        Prepare();
      }
      else if (state == DS18x20SensorState_PrepareComplete && abs(currentTime - lastUpdatedTime) <= SEC_IN_MILLIS) {

        Procceess();
      }
    };

  public:
    void (*UpdateTemperature) (float newValue);

  private:
  void  Prepare () {

      if ( !ds.search(addr)) {

        ds.reset_search();
        return;
      }

      if (OneWire::crc8(addr, 7) != addr[7]) {
          return;
      }

      // the first ROM byte indicates which chip
      switch (addr[0]) {
        case 0x10:
          type_s = 1;
          break;
        case 0x28:
          type_s = 0;
          break;
        case 0x22:
          type_s = 0;
          break;
        default:
          return;
      }

      ds.reset();
      ds.select(addr);
      // ds.write(0x44, 1);        // start conversion, with parasite power on at the end
      state = DS18x20SensorState_PrepareComplete;
    }

  void  Procceess () {

      // delay(1000);

      ds.reset();
      ds.select(addr);
      ds.write(0xBE);

      for ( i = 0; i < 9; i++) {           // we need 9 bytes
        data[i] = ds.read();
      }

      // Convert the data to actual temperature
      // because the result is a 16 bit signed integer, it should
      // be stored to an "int16_t" type, which is always 16 bits
      // even when compiled on a 32 bit processor.
      int16_t raw = (data[1] << 8) | data[0];
      if (type_s) {
        raw = raw << 3; // 9 bit resolution default
        if (data[7] == 0x10) {
          // "count remain" gives full 12 bit resolution
          raw = (raw & 0xFFF0) + 12 - data[6];
        }
      } else {
        byte cfg = (data[4] & 0x60);
        // at lower res, the low bits are undefined, so let's zero them
        if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
        else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
        else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
        //// default is 12 bit resolution, 750 ms conversion time
      }

      float potentialCelcius = (float)raw / 16.0;

      if (potentialCelcius != celsius) {

          celsius = potentialCelcius;
          fahrenheit = celsius * 1.8 + 32.0;

          UpdateTemperature(celsius);
      }

      state = DS18x20SensorState_Waiting;
    };

  private:

    OneWire ds;
  //  int sensorPin;
    byte i;
    // byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius, fahrenheit;

    unsigned long updateInterval;
    unsigned long lastUpdatedTime;

    DS18x20SensorState state;
  };
