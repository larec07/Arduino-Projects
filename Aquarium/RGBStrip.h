class RGBStrip {

public:
  RGBStrip (short redPinValue,
            short greenPinValue,
            short bluePinValue);
  ~RGBStrip ();

public:
// #pragma mark - Enable/Disable strip
  void On ();
  void Off ();
  bool IsOn ();

//
  void SetRGBValues (int, int, int);
  void SetWhiteColorWithGlow (int);

// #pragma mark - Set Constant Colors
    void SetYellowColor ();
    void SetWhiteColor ();
    void SetRedColor ();
    void SetGreenColor ();
    void SetBlueColor ();

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

  short changeInterval;

  bool isOn;

};
