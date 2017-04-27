#include "AquariumManager.h"

AquariumManager::AquariumManager (RGBStrip *lenta) : strip(lenta), lightnessLevel(0) {}

void AquariumManager::UpdateStripByTemperature (float temp)
{
  temperature = temp;

  if (lightnessLevel < ThresholdLightnessValue)
  {
    // Temperature value out of valid value
    if (temperature < TemperatureYelowLowerLimit || temperature > TemperatureYelowUpperLimit)
    {
      strip->SetRedColor();
    }
    // Temperature value in comfort range
    else if (temperature >= TemperatureGreenLowerLimit && temperature <= TemperatureGreenUpperLimit)
    {
      strip->Off();
    }
    else
    {
      strip->SetYellowColor();
    }
  }
}

void AquariumManager::UpdateStripByLightness (int lightness)
{
  lightnessLevel = lightness;

  if (lightnessLevel >= ThresholdLightnessValue)
  {
    int brightness = lightnessLevel/5;

    strip->SetWhiteColorWithGlow(brightness);
  }
}