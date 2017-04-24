/**
  Class define behaviour of Led Strip according to environment(i.e. light and temperature state)
*/
#include "DS18x20.hpp"
#include "RGBStrip.h"

// #pragma mark - Pin Definition
#define STRIPPOWER_PIN 7
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

#define IRPIN 2 // Interruption 1

#define TEMPERATURESENSOR_PIN 6

const short ThresholdLightnessValue = 500;

const short TemperatureYelowUpperLimit = 33;
const short TemperatureGreenUpperLimit = 28;
const short TemperatureGreenLowerLimit = 24;
const short TemperatureYelowLowerLimit = 20;


// class
