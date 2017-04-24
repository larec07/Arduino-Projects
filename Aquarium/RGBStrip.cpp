#include "RGBStrip.h"
#include "NumericHelper.hpp"

static const int MaxGlow = 220;

  RGBStrip::RGBStrip (short powerPinValue,
            short redPinValue,
            short greenPinValue,
            short bluePinValue)
  :
    powerPin(powerPinValue),
    redPin(redPinValue),
    greenPin(greenPinValue),
    bluePin(bluePinValue)
  {

    redValue = 0;
    greenValue = 0;
    blueValue = 0;

    changeInterval = MaxGlow/5;
  }

  RGBStrip::~RGBStrip ()
  {
  }

  void RGBStrip::SetRGBValues (int red, int green, int blue)
  {
    int constrainedRed = Constrain(red, 0, MaxGlow);
    int constrainedGreen = Constrain(green, 0, MaxGlow);
    int constrainedBlue = Constrain(blue, 0, MaxGlow);

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

  void RGBStrip::On ()
  {
    if (isOn)
    {
      return;
    }

    OnStrip();
  }

  void RGBStrip::Off ()
  {
    if (!isOn)
    {
      return;
    }

    OffStrip();
  }

  bool RGBStrip::IsOn ()
  {
    return isOn;
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
