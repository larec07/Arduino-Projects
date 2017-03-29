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
IRrecv irrecv(IRPin);

RGBStrip strip(STRIPPOWER_PIN, RED_PIN, GREEN_PIN, BLUE_PIN);
DS18x20 temperature()

// #pragma mark - Main App Life Cycle
void setup() {

  Serial.begin(9600);

  irrecv.enableIRIn();

  attachInterrupt(1, checkForSignal, CHANGE);

  strip.UpdateStrip = &UpdateStrip;
  strip.OnStrip = &OnStrip;
  strip.OffStrip = &OffStrip;
  pinMode(STRIPPOWER_PIN, OUTPUT);

  temperature.UpdateTemperature =
}

void loop () {
}

// #pragma mark - IRRemote Signal Proccessing
void checkForSignal () {

  decode_results irResults;

  if (irrecv.decode(&irResults)) {

    irrecv.resume();

    proccessSignal (irResults.value, irResults.bits);
  }
}

void proccessSignal (unsigned long value, int bits) {

  // Serial.print("Value = ");
  // Serial.print(value);
  // Serial.print("\tBits = ");
  // Serial.println(bits);

  if (bits == 32) {

    if (value == CODE_HUYNDAI_0) {
      strip.SetWhiteColor();
    }
    else if (value == CODE_HUYNDAI_1) {
      strip.SetRedColor();
    }
    else if (value == CODE_HUYNDAI_2) {
      strip.IncreaseRed();
    }
    else if (value == CODE_HUYNDAI_3) {
      strip.DecreaseRed();
    }
    else if (value == CODE_HUYNDAI_4) {
      strip.SetGreenColor();
    }
    else if (value == CODE_HUYNDAI_5) {
      strip.IncreaseGreen();
    }
    else if (value == CODE_HUYNDAI_6) {
      strip.DecreaseGreen();
    }
    else if (value == CODE_HUYNDAI_7) {
      strip.SetBlueColor();
    }
    else if (value == CODE_HUYNDAI_8) {
      strip.IncreaseBlue();
    }
    else if (value == CODE_HUYNDAI_9) {
      strip.DecreaseBlue();
    }
  }
}
