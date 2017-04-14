#include <IRremote.h>

class IRReceiverWrapper {

public:
  explicit IRReceiverWrapper(short pin) : receiver(IRrecv(pin));

public:
  void (*OnIRSignalReceived) (unsigned long value, int bits);

public:
  void enableIRIn () {

    receiver.enableIRIn();
  };

  void checkForSignal () {

    decode_results irResults;

    if (receiver.decode(&irResults)) {

      receiver.resume();

      proccessSignal (irResults.value, irResults.bits);
    }
  };

private:
  void proccessSignal (unsigned long value, int bits) {

    OnIRSignalReceived(value, bits);
  };

private:
  IRrecv receiver;
};
