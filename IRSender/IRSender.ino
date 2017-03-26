#include <IRremote.h>
#include "TransmittersCodes.h"

#define IRTRANSMITTER_PIN 3
#define IRRECEIVER_PIN 2

IRrecv irreceiver(IRPIN);

decode_results results;

void setup () {

  irreceiver.enableIRIn();

  Serial.begin(9600);
}

void loop () {

  checkIRSensor();
}

#pragma mark - IR Remote Signal

void checkIRSensor () {

  if (irreceiver.decode(&results)) {

    irreceiver.resume();

    processRemoteComand();

    Serial.print ("Value = ");
    Serial.print (results.value);
    Serial.print ("\tBits = ");
    Serial.print (results.bits);
    Serial.print ("========\n");
  }
}

void processRemoteComand () {

  unsigned long value = results.value;

}
