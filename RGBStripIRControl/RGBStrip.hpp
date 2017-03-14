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

    maxGlow = 200;
  }

  ~RGBStrip () {};

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

private:
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

  int maxGlow;

  bool isOn;
};
