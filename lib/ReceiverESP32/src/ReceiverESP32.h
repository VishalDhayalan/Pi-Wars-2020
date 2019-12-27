#ifndef ReceiverESP32_h
#define ReceiverESP32_h

#include <Arduino.h>
#include <FunctionalInterrupt.h>

class Channel {
  private:
    int _pin;
    unsigned long _timeout;
    volatile unsigned long start_t;
    volatile unsigned long _pulse_t;

    void IRAM_ATTR compute();

  public:        
    Channel(int pin, unsigned long timeout);
    int getPin();
    volatile unsigned long pulse();
    volatile int position();
    bool active();
};
#endif