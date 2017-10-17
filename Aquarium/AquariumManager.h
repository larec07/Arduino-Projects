/**
  Class define behaviour of Led Strip according to environment(i.e. light and temperature state)
*/
#include "DS18x20.h"
#include "RGBStrip.h"

// #pragma mark - Pin Definition
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 6

#define IRPIN 2 // Interruption 1

#define TEMPERATURESENSOR_PIN A1

#define LIGHTNESS_PIN A0

const int ThresholdLightnessValue = 800; /// 900 - optimal for Iskra Neo, but Iskra Mini has another behavior with the same value (strange...)

const short TemperatureYelowUpperLimit = 33;
const short TemperatureGreenUpperLimit = 28;
const short TemperatureGreenLowerLimit = 24;
const short TemperatureYelowLowerLimit = 20;

class AquariumManager
{
  public:
    AquariumManager (RGBStrip *);

    void UpdateStripByTemperature (float);
    void UpdateStripByLightness (int);

  private:
    void OnTemperatureChanged ();
    void OnLightnessChanged ();

  private:
    RGBStrip *strip;
    int lightnessLevel;
    float temperature;
};
