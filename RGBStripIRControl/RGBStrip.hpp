#include "Updatable.hpp"

class RGBStrip {

public:
  RGBStrip (short redPinValue,
            short greenPinValue,
            short bluePinValue)
  :
    redPin(redPinValue),
    greenPin(greenPinValue),
    bluePin(bluePinValue)
  {
    redValue = 0;
    greenValue = 0;
    blueValue = 0;
  }

  ~RGBStrip ();

  void SetRGBValues (int red, int green, int blue)
  {
    if (red != redValue || green != greenValue || blue != blueValue)
    {
      redValue = red;
      greenValue = green;
      blueValue = blue;
    }
  }

private:
  short redPin;
  short greenPin;
  short bluePin;

  int redValue;
  int greenValue;
  int blueValue;
};
