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
  if (abs(lightnessLevel - lightness) < 50)
    return;

  lightnessLevel = lightness;

  OnLightnessChanged();
}

void AquariumManager::OnTemperatureChanged ()
{
  if (lightnessLevel < ThresholdLightnessValue)
  {
    // Temperature value out of valid value
    if (temperature < TemperatureYelowLowerLimit || temperature > TemperatureYelowUpperLimit)
    {
      strip->SetRedColor(100);
    }
    // Temperature value in comfort range
    else if (temperature >= TemperatureGreenLowerLimit && temperature <= TemperatureGreenUpperLimit)
    {
      strip->Off();
    }
    else
    {
      strip->SetYellowColor(100);
    }
  }
}

void AquariumManager::OnLightnessChanged ()
{
  if (lightnessLevel >= ThresholdLightnessValue)
  {
    int brightness = Map(lightnessLevel, ThresholdLightnessValue, 1023, 60, 255);

    strip->SetWhiteColorWithGlow(brightness);
  }
  else
  {
    OnTemperatureChanged();
  }
}
