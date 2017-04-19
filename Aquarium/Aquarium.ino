#include <IRremote.h>

#include "AquariumManager.hpp"
#include "TransmittersCodes.h"

// #pragma mark - Pin Definition
#define STRIPPOWER_PIN 7
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

#define IRPin 2 // Interruption 1

#define TEMPERATURESENSOR_PIN 6

RGBStrip strip(STRIPPOWER_PIN, RED_PIN, GREEN_PIN, BLUE_PIN);
DS18x20 temperature(TEMPERATURESENSOR_PIN);

int lightLevel = 0;

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

  if (lightLevel < ThresholdLightnessValue) {

    // Temperature value out of valid value
    if (value < TemperatureYelowLowerLimit || value > TemperatureYelowUpperLimit) {

      strip.SetRedColor();
    }
    // Temperature value in comfort range
    else if (value >= TemperatureGreenLowerLimit && value <= TemperatureGreenUpperLimit) {

      strip.Off();
    }
    else {

      strip.SetYellowColor();
    }
  }
}

// #pragma mark - Global Variables
volatile IRrecv irrecv(IRPin);

// #pragma mark - Main App Life Cycle
void setup() {

  Serial.begin(9600);

  irrecv.enableIRIn();

//  attachInterrupt(1, checkForSignal, CHANGE);

  strip.UpdateStrip = &UpdateStrip;
  strip.OnStrip = &OnStrip;
  strip.OffStrip = &OffStrip;
  pinMode(STRIPPOWER_PIN, OUTPUT);

  temperature.UpdateTemperature = &UpdateTemperature;
  temperature.MakeDelay = &MakeDelay;
  temperature.DebugPrint = &DebugPrint;
}

void loop () {

  temperature.Update(millis());
}
