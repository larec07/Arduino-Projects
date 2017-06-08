#include "AquariumManager.h"
#include "NumericHelper.hpp"

AquariumManager::AquariumManager (RGBStrip *lenta) : strip(lenta), lightnessLevel(0), temperature(0) {}

void AquariumManager::UpdateStripByTemperature (float temp)
{
  if (abs(temp - temperature) < 1.0f)
    return;

  temperature = temp;

  OnTemperatureChanged();
}

void AquariumManager::UpdateStripByLightness (int lightness)
{
  if (abs(lightnessLevel - lightness) < 10)
    return;

  lightnessLevel = lightness;

  OnLightnessChanged();
}

void AquariumManager::OnTemperatureChanged ()
{
  if (lightnessLevel < ThresholdLightnessValue)
  {
    // Temperature value greater than necessary
    if (temperature > TemperatureGreenUpperLimit)
    {
      int brightness = Map(temperature, TemperatureGreenUpperLimit, TemperatureYelowUpperLimit, 1, MaxGlow);
      strip->SetRedColor(brightness);
    }
    // Temperature value less than necessary
    else if (temperature < TemperatureGreenLowerLimit)
    {
      int brightness = Map(temperature, TemperatureGreenLowerLimit, TemperatureYelowLowerLimit, 1, MaxGlow);
      strip->SetBlueColor(brightness);
    }
    // Temperature value in comfort range
    else
    {
      strip->Off();
    }
  }
}

void AquariumManager::OnLightnessChanged ()
{
  if (lightnessLevel >= ThresholdLightnessValue)
  {
    int brightness = Map(lightnessLevel, ThresholdLightnessValue, 1023, 60, MaxGlow);

    strip->SetWhiteColor(brightness);
  }
  else
  {
    OnTemperatureChanged();
  }
}
