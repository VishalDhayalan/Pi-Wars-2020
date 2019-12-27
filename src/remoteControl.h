#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <Arduino.h>
#include <MotorESP32.h>
#include <Servo.h>

void arcadeDrive(Motor& right, Motor& left, int thr, int rud);
void ackermannDrive(Motor& right, Motor& left, int thr, int rud, Servo& steering);
#endif