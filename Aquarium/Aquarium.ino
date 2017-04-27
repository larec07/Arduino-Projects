#include <IRremote.h>

#include "AquariumManager.h"
#include "TransmittersCodes.h"
//#include "TimeConstants.h"

RGBStrip strip(STRIPPOWER_PIN, RED_PIN, GREEN_PIN, BLUE_PIN);
DS18x20 temperature(TEMPERATURESENSOR_PIN);

AquariumManager stripManager(&strip);

// #pragma mark - Common Delegation
void MakeDelay (unsigned long value) {

  delay(value);
}

void DebugPrint (char *text) {

  Serial.println(text);
}
// #pragma mark - RGBStrip Delegate
void UpdateStrip (int r, int g, int b) {

  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void OnStrip () {

  digitalWrite(STRIPPOWER_PIN, HIGH);
}

void OffStrip () {

  digitalWrite(STRIPPOWER_PIN, LOW);
}

// #pragma mark - DS18x20Delegate
void UpdateTemperature (float value) {

  stripManager.UpdateStripByTemperature(value);
}

// #pragma mark - Main App Life Cycle
void setup() {

  Serial.begin(9600);

//  irrecv.enableIRIn();

//  attachInterrupt(1, checkForSignal, CHANGE);

  strip.UpdateStrip = &UpdateStrip;
  strip.OnStrip = &OnStrip;
  strip.OffStrip = &OffStrip;
  pinMode(STRIPPOWER_PIN, OUTPUT);

  temperature.UpdateTemperature = &UpdateTemperature;
  temperature.DebugPrint = &DebugPrint;
}

void loop () {

  temperature.Update(millis());
}
