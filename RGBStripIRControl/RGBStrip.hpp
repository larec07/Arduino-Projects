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

    maxGlow = 200;

    isOn = false;
  }

  ~RGBStrip ();

  void SetRGBValues (int red, int green, int blue)
  {
    int constrainedRed = constrain(red, 0, maxGlow);
    int constrainedGreen = constrain(green, 0, maxGlow);
    int constrainedBlue = constrain(blue, 0, maxGlow);

    if (constrainedRed != redValue
      || constrainedGreen != greenValue
      || constrainedBlue != blueValue)
    {
      redValue = constrainedRed;
      greenValue = constrainedGreen;
      blueValue = constrainedBlue;

      OnRGBValuesChanged();
    }
  }

  void On ()
  {
    if (isOn)
    {
      return;
    }

    if (redValue == greenValue == blueValue == 0)
    {
      int middleValue = maxGlow/2;

      SetRGBValues(middleValue, middleValue, middleValue);
    }
    else
    {
      OnRGBValuesChanged();
    }
  }

  void Off ()
  {
    if (!isOn)
    {
      return;
    }

    
  }

private:
  void OnRGBValuesChanged ()
  {
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
  }


private:
  short redPin;
  short greenPin;
  short bluePin;

  int redValue;
  int greenValue;
  int blueValue;

  int maxGlow;

  bool isOn;
};
