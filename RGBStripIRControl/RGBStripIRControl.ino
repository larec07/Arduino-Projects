#include "RGBStrip.hpp"
#include "TransmittersCodes.h"

// #pragma mark - Pin Definition
#define STRIPPOWER_PIN 2
#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

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

// #pragma mark - Main App Life Cycle
volatile RGBStrip strip(STRIPPOWER_PIN, RED_PIN, GREEN_PIN, BLUE_PIN);

void setup() {

  strip.UpdateStrip = &UpdateStrip;
  strip.OnStrip = &OnStrip;
  strip.OffStrip = &OffStrip;
  pinMode(STRIPPOWER_PIN, OUTPUT);
}

void loop () {
}
