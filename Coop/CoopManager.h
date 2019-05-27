/* Device consist of:
                     - Water bowl:
                       * Water tap: filling drinking bowl. Controled by statements of water level
                       * Hall's sensor: provides water level in drinking bowl
                      
                     - Lightness and warmth:
                       * Infra-red lamp: gives light and warmth. Controled by statements of tempperature and lightness level
                       * Lightness sensor: provides lightness level to handle the lamp through relay module
                       * DS 18B20 sensor: provides temperature data

  Main interface is CoopManager
                      
*/

// Pins definition
#define WaterCap_Pin 3
#define HallSensor_Pin A0
#define Relay_Pin 4
#define LightnessSensor_Pin A1
#define DS18B20
