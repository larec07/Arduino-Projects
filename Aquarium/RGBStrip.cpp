#include "RGBStrip.h"
#include "NumericHelper.hpp"

static const int MaxGlow = 200;

  RGBStrip::RGBStrip (short redPinValue,
                      short greenPinValue,
                      short bluePinValue)
  :
    redPin(redPinValue),
    greenPin(greenPinValue),
    bluePin(bluePinValue)
  {
    isOn = false;

    redValue = -1;
    greenValue = -1;
    blueValue = -1;

    changeInterval = MaxGlow/5;
  }

  RGBStrip::~RGBStrip () {}

  void RGBStrip::On ()
  {
    // if (isOn)
    // {
    //   return;
    // }
    //
    // isOn = true;

    SetWhiteColorWithGlow(MaxGlow);
  }

  void RGBStrip::Off ()
  {
    // if (!isOn)
    // {
    //   return;
    // }
    //
    // isOn = false;

    SetWhiteColorWithGlow(0);
  }

  bool RGBStrip::IsOn ()
  {
    return isOn;
  }

  void RGBStrip::SetRGBValues (int red, int green, int blue)
  {
    int constrainedRed = Constrain(red, 0, MaxGlow);
    int constrainedGreen = Constrain(green, 0, MaxGlow);
    int constrainedBlue = Constrain(blue, 0, MaxGlow);

    if (constrainedRed == redValue &&
        constrainedGreen == greenValue &&
        constrainedBlue  == blueValue)
        {
          return;
        }

    redValue = constrainedRed;
    greenValue = constrainedGreen;
    blueValue = constrainedBlue;

    OnRGBValuesChanged();
  }

  void RGBStrip::SetWhiteColorWithGlow (int glow)
  {
    SetRGBValues(glow, glow, glow);
  }

// #pragma mark - Increment/Decrement each component separately
/// Red
  void RGBStrip::IncreaseRed ()
  {
    ProcessComponent(redValue, redValue + changeInterval);
  }

  void RGBStrip::DecreaseRed ()
  {
    ProcessComponent(redValue, redValue - changeInterval);
  }
/// Green
  void RGBStrip::IncreaseGreen ()
  {
    ProcessComponent(greenValue, greenValue + changeInterval);
  }

  void RGBStrip::DecreaseGreen ()
  {
    ProcessComponent(greenValue, greenValue - changeInterval);
  }
/// Blue
  void RGBStrip::IncreaseBlue ()
  {
    ProcessComponent(blueValue, blueValue + changeInterval);
  }

  void RGBStrip::DecreaseBlue ()
  {
    ProcessComponent(blueValue, blueValue - changeInterval);
  }

// #pragma mark - Set Constant Colors
  void RGBStrip::SetYellowColor ()
  {
    SetRGBValues(MaxGlow, MaxGlow, 0);
  }

  void RGBStrip::SetWhiteColor ()
  {
      SetRGBValues(MaxGlow, MaxGlow, MaxGlow);
  }

  void RGBStrip::SetRedColor ()
  {
    SetRGBValues(MaxGlow, 0, 0);
  }

  void RGBStrip::SetGreenColor ()
  {
    SetRGBValues(0, MaxGlow, 0);
  }

  void RGBStrip::SetBlueColor ()
  {
    SetRGBValues(0, 0, MaxGlow);
  }

  void RGBStrip::ProcessComponent (int &currentValue, int newValue)
  {
    int considerValue = Constrain(newValue, 0, MaxGlow);

    if (considerValue != currentValue)
    {
      currentValue = considerValue;
      OnRGBValuesChanged();
    }
  }

  void RGBStrip::OnRGBValuesChanged ()
  {
    UpdateStrip(redValue, greenValue, blueValue);
  }
