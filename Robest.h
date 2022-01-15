#ifndef Robest_H
#define Robest_H
#include "Arduino.h"
#include <Servo.h>
class Robest {
public:
  Robest(int r1, int r2, int l1, int l2, int spd);
  Servo s1;
  Servo s2;
  Servo s3;
  bool pass;
  bool S1,S2,S3;
  float BatteryRead, BatteryValue;

  int RedVal;
  int GreenVal;
  int BlueVal;
  int _l1;
  int _l2;
  int _r1;
  int _r2;
  int _spd;

  char data;

  void enableServo1(bool on1);
  void enableServo2(bool on2);
  void enableServo3(bool on3);
  void testRun();
  void autoRunBT();
  void init(int baud);
  void forward();
  void stop();
  void backward();
  void right();
  void left();
  void setSpeed(int SPD);
  void checkBat(int OPT);
  int getSliderVal1();
  int getSliderVal2();
  int getSliderVal3();

};


#endif
