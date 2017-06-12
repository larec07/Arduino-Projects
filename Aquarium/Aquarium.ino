#include <IRremote.h>

#include "AquariumManager.h"
#include "TransmittersCodes.h"

RGBStrip strip(RED_PIN, GREEN_PIN, BLUE_PIN);
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

// #pragma mark - DS18x20Delegate
void UpdateTemperature (float value) {

  stripManager.UpdateStripByTemperature(value);
}

// #pragma mark - Main App Life Cycle
void setup() {

  Serial.begin(9600);

//  irrecv.enableIRIn();

//  attachInterrupt(1, checkForSignal, CHANGE);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00);

  strip.UpdateStrip = &UpdateStrip;

  temperature.UpdateTemperature = &UpdateTemperature;
  temperature.DebugPrint = &DebugPrint;
}

void loop () {

  temperature.Update(millis());
  stripManager.UpdateStripByLightness(analogRead(LIGHTNESS_PIN));
}
