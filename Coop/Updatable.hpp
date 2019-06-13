#include "TimeConstants.h"

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
  virtual void Trigger() = 0;

 private:
  Milliseconds absoluteValue (Milliseconds originValue) 
  {
    return originValue > 0 ? originValue : - originValue;
  }

private:
  Milliseconds triggerInterval;
  Milliseconds prevTriggeredTime;
};
