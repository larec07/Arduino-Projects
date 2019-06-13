#include "CoopManager.h"

CoopManager coop(MINUTE_IN_MILLIS * 1);

void setup() {
  // put your setup code here, to run once:

  if (abs(5 - 6) > 4) {

    
  }
}

void loop() {
  
  coop.Update(millis());
}
