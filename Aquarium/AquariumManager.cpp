#include "AquariumManager.h"

AquariumManager::AquariumManager (RGBStrip *lenta) : strip(lenta), lightLevel(0) {}

void AquariumManager::OnTemperatureChanged (float temperature)
{
  if (lightLevel < ThresholdLightnessValue)
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

void AquariumManager::OnLightnessChanged (int lightness)
{
  if ()
}
