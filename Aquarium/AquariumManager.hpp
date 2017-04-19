/**
  Class define behaviour of Led Strip according to environment(i.e. light and temperature state)
*/
#include "DS18x20.hpp"
#include "RGBStrip.hpp"

const short ThresholdLightnessValue = 500;

const short TemperatureYelowUpperLimit = 33;
const short TemperatureGreenUpperLimit = 28;
const short TemperatureGreenLowerLimit = 24;
const short TemperatureYelowLowerLimit = 20;


// class
