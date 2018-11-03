class Updatable {

typedef unsigned long Milliseconds;

public:
  Updatable (Milliseconds interval) : triggerInterval(interval);
  void Update(Milliseconds currentTime)
  {
     if (abs(currentTime - prevTriggeredTime) >= triggerInterval)
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
}
