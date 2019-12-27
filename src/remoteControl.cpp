#include "remoteControl.h"

void arcadeDrive(Motor& right, Motor& left, int thr, int rud) {
  // compute arcade
  int ch_R, ch_L;
  if (abs(thr) < 5) {
    thr = 0;
  }
  if (abs(rud) < 5) {
    rud = 0;
  }
  ch_R = thr - rud;
  ch_L = thr + rud;
  ch_R = constrain(ch_R, -100, 100);
  ch_L = constrain(ch_L, -100, 100);
  
  // Drive motors accordingly
  if (ch_R >=0) {
    // Serial.print((String)"R: " + map(ch_R, 0, 100, 0, 255) + " , ");
    right.forward(map(ch_R, 0, 100, 0, 255));
  }
  else {
    // Serial.print((String)"R: " + map(ch_R, -100, 0, -255, 0) + " , ");
    right.reverse(map(ch_R, -100, 0, 255, 0));
  }
  if (ch_L >= 0) {
    // Serial.println((String)"L: " + map(ch_L, 0, 100, 0, 255));
    left.forward(map(ch_L, 0, 100, 0, 255));
  }
  else {
    // Serial.println((String)"L: " + map(ch_L, -100, 0, -255, 0));
    left.reverse(map(ch_L, -100, 0, 255, 0));
  }
  // Serial.println((String)"rps_R: " + right.rps() + " | rps_L: " + left.rps());
}

void ackermannDrive(Motor& right, Motor& left, int thr, int rud, Servo& steering) {
  // Drive Motors accordingly. Deadband: -5 < throttle < 5
  if (thr <= -5) {
    right.reverse(map(thr, -100, 0, 255, 0));
    left.reverse(map(thr, -100, 0, 255, 0));
  }
  else if (thr >= 5) {
    right.forward(map(thr, 0, 100, 0, 255));
    left.forward(map(thr, 0, 100, 0, 255));
  }
  else {
    right.coast();
    left.coast();
  }
  
  int steering_angle = map(rud, -90, 90, 120, 50);
  if (abs(rud) <= 3) {
    steering_angle = 85;
  }

  steering.write(steering_angle);
  Serial.println((String)"deg: " + steering_angle + "\teffective: " + (steering_angle + 5));
}