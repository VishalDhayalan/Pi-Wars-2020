#include <Arduino.h>
#include <Servo.h>
#include <ReceiverESP32.h>
#include <MotorESP32.h>
#include "remoteControl.h"

String rec;                     // String to store response

Channel rudder = Channel(32, 20000);
Channel throttle = Channel(33, 20000);
Channel gear_sw = Channel(25, 20000);
Channel knob = Channel(26, 20000);
Channel aux_throttle = Channel(27, 20000);

Motor drive_R = Motor(0, 23, 18, 19, 35, 11, 34.02);
Motor drive_L = Motor(1, 5, 16, 17, 34, 11, 34.02);

Servo steeringServo;

// Handles RC Challenges
void RC_Challenge(String challenge) {

}

void setup() {
  Serial.begin(115200);
  steeringServo.attach(4, 2, 0, 180, 680, 2240);

  // // Wait for RPi to boot and send "Pi Ready"
  // while (rec != "Pi Ready.") { 
  //   if (Serial.available()) {
  //     rec = Serial.readString();
  //   }
  //   delay(5);
  // }
  // Serial.println("OK");           // Reply to "Pi Ready" with "OK"
  // Serial.println("ESP Ready.");   // Send "ESP Ready"
  // // Wait for "OK" reply from RPi
  // while (rec != "OK") {
  //   if (Serial.available()) {
  //     rec = Serial.readString();
  //   }
  //   delay(5);
  // }
  // rec = "";
  // // ---------- UART Handshake with RPi Complete! ---------- //
}

void loop() {
  // while (!Serial.available()) {}
  // rec = Serial.readString();
  // if (rec == "Challenge: Pi Noon") {
  //   RC_Challenge("Pi Noon");
  // }
  if (throttle.active()) {
    if (gear_sw.position() < 50) {
      ackermannDrive(drive_R, drive_L, throttle.position(), rudder.position(), steeringServo);
    }
    else {
      arcadeDrive(drive_R, drive_L, throttle.position(), rudder.position());
    }
  }
  else {
    Serial.println("Signal Lost...");
    drive_R.brake();
    drive_L.brake();
    while (!throttle.active()) {
      delay(5);
    }
  }
}