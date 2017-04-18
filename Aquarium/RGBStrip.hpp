
static const int MaxGlow = 220;

class RGBStrip {

public:
  RGBStrip (short powerPinValue,
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

  ~RGBStrip () {};

  void SetRGBValues (int red, int green, int blue)
  {
    int constrainedRed = constrain(red, 0, MaxGlow);
    int constrainedGreen = constrain(green, 0, MaxGlow);
    int constrainedBlue = constrain(blue, 0, MaxGlow);

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

    OnStrip();
  }

  void Off ()
  {
    if (!isOn)
    {
      return;
    }

    OffStrip();
  }

  bool IsOn ()
  {
    return isOn;
  }

// #pragma mark - Increment/Decrement each component separately
/// Red
  void IncreaseRed ()
  {
    ProcessComponent(redValue, redValue + changeInterval);
  }

  void DecreaseRed ()
  {
    ProcessComponent(redValue, redValue - changeInterval);
  }
/// Green
  void IncreaseGreen ()
  {
    ProcessComponent(greenValue, greenValue + changeInterval);
  }

  void DecreaseGreen ()
  {
    ProcessComponent(greenValue, greenValue - changeInterval);
  }
/// Blue
  void IncreaseBlue ()
  {
    ProcessComponent(blueValue, blueValue + changeInterval);
  }

  void DecreaseBlue ()
  {
    ProcessComponent(blueValue, blueValue - changeInterval);
  }

// #pragma mark - Set Constant Colors
  void SetWhiteColor ()
  {
      SetRGBValues(MaxGlow, MaxGlow, MaxGlow);
  }

  void SetRedColor ()
  {
    SetRGBValues(MaxGlow, 0, 0);
  }

  void SetGreenColor ()
  {
    SetRGBValues(0, MaxGlow, 0);
  }

  void SetBlueColor ()
  {
    SetRGBValues(0, 0, MaxGlow);
  }

private:
  void ProcessComponent (int &currentValue, int newValue)
  {
    int considerValue = constrain(newValue, 0, MaxGlow);

    if (considerValue != currentValue)
    {
      currentValue = considerValue;
      OnRGBValuesChanged();
    }
  }

  void OnRGBValuesChanged ()
  {
    UpdateStrip(redValue, greenValue, blueValue);
  }

public:
  void (*UpdateStrip) (int, int, int);
  void (*OnStrip) ();
  void (*OffStrip) ();

private:
  short powerPin;

  short redPin;
  short greenPin;
  short bluePin;

  int redValue;
  int greenValue;
  int blueValue;

  short changeInterval;

  bool isOn;
};
