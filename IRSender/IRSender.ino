#include <IRremote.h>

#define IRTRANSMITTER_PIN 3
#define IRRECEIVER_PIN 2

IRrecv irreceiver(IRPIN);

decode_results results;
