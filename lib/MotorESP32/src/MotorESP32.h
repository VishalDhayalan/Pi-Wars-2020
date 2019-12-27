#ifndef MotorESP32_h
#define MotorESP32_h

#include <Arduino.h>
#include <FunctionalInterrupt.h>

class Motor {
  private:
    int pwm_ch, IN1, IN2;
    float _PPR, reduction_ratio, RPS;
    volatile unsigned long enc_pulses, enc_time;

    void IRAM_ATTR encoder_ISR();

  public:
    Motor(int pwm_channel, int pwm_pin, int IN1_pin, int IN2_pin, int enc_pin, float PPR, float ratio);
    void forward(int pwm_speed);
    void reverse(int pwm_speed);
    void coast();
    void brake();
    float rps();
};
#endif