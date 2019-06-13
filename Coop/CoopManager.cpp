#include "CoopManager.h"

CoopManager::CoopManager(Milliseconds interval) 
  : isRelayTurnedOn(false), 
    threashold_Lightness (180), 
    threashold_Temperature(25),
    ds18x20Sensor(DS18x20(DS18B20_Pin, interval))
{
//  ds18x20Sensor.UpdateTemperature = &UpdateTemperature;
  pinMode(OUTPUT, Relay_Pin);
  digitalWrite(Relay_Pin, LOW);

  auto absolute = [](float value) {/*UpdateTemperature(value);*/};

  ds18x20Sensor.UpdateTemperature = absolute;
}

void CoopManager::Update (Milliseconds currentTime)
{
  ds18x20Sensor.Update(currentTime);
}

void CoopManager::SwitchRelay(bool on)
{
  if (on != isRelayTurnedOn) 
  {
    digitalWrite(Relay_Pin, on ? HIGH : LOW);
    isRelayTurnedOn = on;
  }
}

void CoopManager::UpdateTemperature (float value)
{
  
}
