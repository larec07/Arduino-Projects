#include <RGBStrip.hpp>

#define STRIPPOWER_PIN 2
#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

RGBStrip strip = RGBStrip(STRIPPOWER_PIN, RED_PIN, GREEN_PIN, BLUE_PIN);

void setup() {

  pinMode(STRIPPOWER_PIN, OUTPUT);
}


#pragma mark - RGBStrip Delegate
void OnSripValuesChanged (int r, int g, int b) {

  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}
