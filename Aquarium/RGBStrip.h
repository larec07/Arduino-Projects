static const int MaxGlow = 200;

class RGBStrip {

public:
  RGBStrip (short, short, short);
  ~RGBStrip ();

public:
// #pragma mark - Enable/Disable strip
  void On ();
  void Off ();
  bool IsOn ();

//
  void SetRGBValues (int, int, int);

// #pragma mark - Set Constant Colors
    void SetWhiteColor (int brightness = MaxGlow);
    void SetYellowColor (int brightness = MaxGlow);
    void SetRedColor (int brightness = MaxGlow);
    void SetGreenColor (int brightness = MaxGlow);
    void SetBlueColor (int brightness = MaxGlow);

// #pragma mark - Increment/Decrement each component separately
    /// Red
    void IncreaseRed ();
    void DecreaseRed ();
    /// Green
    void IncreaseGreen ();
    void DecreaseGreen ();
    /// Blue
    void IncreaseBlue ();
    void DecreaseBlue ();

public:
  void (*UpdateStrip) (int, int, int);
  // void (*OnStrip) ();
  // void (*OffStrip) ();

private:
  void ProcessComponent (int &, int);
  void OnRGBValuesChanged ();

private:
  // short powerPin;

  short redPin;
  short greenPin;
  short bluePin;

  int redValue;
  int greenValue;
  int blueValue;

  int preferedValueRed;
  int preferedValueGreen;
  int preferedValueBlue;

  short changeInterval;

  bool isOn;

};
