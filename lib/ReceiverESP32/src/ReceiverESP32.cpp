#include "ReceiverESP32.h"

Channel::Channel(int pin, unsigned long timeout) {
  _pin = pin;
  _timeout = timeout;
  start_t = 0;
  _pulse_t = 0;
  pinMode(_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(_pin), std::bind(&Channel::compute, this), CHANGE);
}

void IRAM_ATTR Channel::compute() {
  if (digitalRead(_pin)) {
    start_t = micros();
  }
  else {
    unsigned volatile long temp = micros();
    // Update _pulse_t only if an edge was NOT missed (aka the pulse width is less than the timeout set)
    if ((temp - start_t) <= _timeout) {
      _pulse_t = temp - start_t;
    }
  }
}

int Channel::getPin() {
  return _pin;
}

volatile unsigned long Channel::pulse() {
  return _pulse_t;
}

volatile int Channel::position() {
  int pos = map(_pulse_t, 1000, 2000, -100, 100);
  return constrain(pos, -100, 100);
}

bool Channel::active() {
  if ((micros() - start_t) > 2.5*_timeout) {
    return false;
  }
  return true;
}