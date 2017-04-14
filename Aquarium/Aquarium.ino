#include <IRremote.h>

#include "RGBStrip.hpp"
#include "TransmittersCodes.h"
#include "DS18x20.hpp"

// #pragma mark - Pin Definition
#define STRIPPOWER_PIN 7
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

#define IRPin 2 // Interruption 1

#define TEMPERATURESENSOR_PIN 6

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

  Serial.print("Temp = ");
  Serial.println(value);
}

// #pragma mark - Global Variables
volatile IRrecv irrecv(IRPin);

RGBStrip strip(STRIPPOWER_PIN, RED_PIN, GREEN_PIN, BLUE_PIN);
DS18x20 temperature(TEMPERATURESENSOR_PIN);

// #pragma mark - Main App Life Cycle
void setup() {

  Serial.begin(9600);

  irrecv.enableIRIn();

  attachInterrupt(1, checkForSignal, CHANGE);

  strip.UpdateStrip = &UpdateStrip;
  strip.OnStrip = &OnStrip;
  strip.OffStrip = &OffStrip;
  pinMode(STRIPPOWER_PIN, OUTPUT);

 // temperature.UpdateTemperature = &UpdateTemperature;
}

void loop () {
}
