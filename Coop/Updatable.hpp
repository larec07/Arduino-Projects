#include "TimeConstants.h"

Milliseconds absoluteValue (Milliseconds originValue) {

  return originValue > 0 ? originValue : - originValue;
}

class Updatable {

public:
  Updatable (Milliseconds interval) : triggerInterval(interval) {};
  void Update(Milliseconds currentTime)
  {
     if (absoluteValue(currentTime - prevTriggeredTime) >= triggerInterval)
     {
       prevTriggeredTime = currentTime;

       Trigger();
     }
  };

protected:
  virtual void Trigger();

private:
  Milliseconds triggerInterval;
  Milliseconds prevTriggeredTime;
};
