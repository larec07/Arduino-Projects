#include "TimeConstants.h"

#include <OneWire.h>

typedef enum
  {
    DS18x20SensorState_Waiting,
    DS18x20SensorState_PrepareComplete,
  } DS18x20SensorState;

  class DS18x20 {

  public:
    DS18x20 (uint8_t, Milliseconds timeInterval = 60000);
    void Update (Milliseconds);
    
// #pragma mark - DS18x20 Delegate
  public:
    void (*UpdateTemperature) (float);
    void (*DebugPrint) (char *);

  private:
    void  Prepare ();
    void  Proccess ();

  private:
    OneWire ds;
    byte i;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius, fahrenheit;

    Milliseconds updateInterval;
    Milliseconds lastUpdatedTime;

    DS18x20SensorState state;
  };
