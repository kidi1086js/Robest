#ifndef Robest_H
#define Robest_H
#include "Arduino.h"

class Robest {
public:
  Robest(int r1, int r2, int l1, int l2, int spd);

  bool pass;
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
};


#endif