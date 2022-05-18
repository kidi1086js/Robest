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
  bool OASEN, OASisinitiated = 0;
  bool obstacle = 0;
  bool fwd;
  bool lightattach, hornattach, pwm0attach, pwm1attach, pwm2attach = 0;
  float BatteryRead, BatteryValue, distance, duration;
  float BattPercentage;
  int x;
  int RedVal;
  int GreenVal;
  int BlueVal;
  int _l1;
  int _l2;
  int _r1;
  int _r2;
  int _spd;
  int minOASdistance;
  int echo;
  int trig;

  char data;

  void IOinit(int pin, char BTVAL, char btval);
  void PWM0init(bool PWM0ATTACH);
  void PWM1init(bool PWM1ATTACH);
  void PWM2init(bool PWM2ATTACH);
  void lightinit(bool LIGHTATTACH);
  void horninit(bool HORNATTACH);
  void PWM0();
  void PWM1();
  void PWM2();
  void light();
  void horn();
  void OASinit(int ECHO, int TRIG);
  void OAS();
  void enableServo1(bool on1);
  void enableServo2(bool on2);
  void enableServo3(bool on3);
  void lineFollower();
  void Read();
  void testRun();
  void run();
  void autoRunBT();
  void init(unsigned long baud);
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
  char getdata();
  float BatteryLevel();

};


#endif
