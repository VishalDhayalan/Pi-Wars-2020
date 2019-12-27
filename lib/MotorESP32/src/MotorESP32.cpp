#include "MotorESP32.h"

Motor::Motor(int pwm_channel, int pwm_pin, int IN1_pin, int IN2_pin, int enc_pin, float PPR, float ratio) {
    pwm_ch = pwm_channel;
    IN1 = IN1_pin;
    IN2 = IN2_pin;
    _PPR = PPR;
    reduction_ratio = ratio;
    enc_pulses = 0;

    ledcSetup(pwm_ch, 5000, 8);
    ledcAttachPin(pwm_pin, pwm_ch);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    coast();

    pinMode(enc_pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(enc_pin), std::bind(&Motor::encoder_ISR, this), FALLING);
    enc_time = micros();
}

void IRAM_ATTR Motor::encoder_ISR() {
    enc_pulses++;
}

void Motor::forward(int pwm_speed) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    ledcWrite(pwm_ch, pwm_speed);
}

void Motor::reverse(int pwm_speed) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(pwm_ch, pwm_speed);
}

void Motor::coast() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    ledcWrite(pwm_ch, 0);
}

void Motor::brake() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    ledcWrite(pwm_ch, 0);
}

float Motor::rps() {
    unsigned long t = (micros() - enc_time) / 1000000;
    if (t >= 0.05) {
    RPS = enc_pulses / (_PPR * reduction_ratio * t);
    enc_pulses = 0;
    enc_time = micros();
    }
    return RPS;
}