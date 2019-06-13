#include "Updatable.hpp"
#include "DS18x20.h"

/* Device consist of:
                     - Water bowl:
                       * Water tap: filling drinking bowl. Controled by statements of water level
                       * Hall's sensor: provides water level in drinking bowl
                      
                     - Lightness and warmth:
                       * Infra-red lamp: gives light and warmth. Controled by statements of tempperature and lightness level
                       * Lightness sensor: provides lightness level to handle the lamp through relay module
                       * DS 18B20 sensor: provides temperature data
  
  Threashold values of params should set through Bluetooth interface.

  Main interface is CoopManager               
*/

// Pins definition
#define WaterCap_Pin 3
#define HallSensor_Pin A0
#define Relay_Pin 4
#define LightnessSensor_Pin A2
#define DS18B20_Pin A1

class CoopManager {

  public:
    CoopManager (Milliseconds interval = MINUTE_IN_MILLIS * 10);
    void Update (Milliseconds);

  private:
    void UpdateTemperature (float);
   // Lamp control
    void SwitchRelay(bool);
    void CheckTemperatureAndLightnessStatements ();

   
  private:
    DS18x20 ds18x20Sensor;
    bool isRelayTurnedOn;
    short temperature;
    short lightness;
   
  // Threashold values of sensor statements
  private: 
    short threashold_Lightness;
    short threashold_Temperature;
};
