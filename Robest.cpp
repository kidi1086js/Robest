#include "Robest.h"

Robest::Robest(int r1, int r2, int l1, int l2, int spd) {

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(spd, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  _l1 = l1;
  _l2 = l2;
  _r1 = r1;
  _r2 = r2;
  _spd = spd;
}


void Robest::init(int baud) {
  Serial.begin(baud);
}

void Robest::setSpeed(int SPD) {
  analogWrite(_spd, SPD);
}

void Robest::stop() {
  digitalWrite(_l1, LOW);
  digitalWrite(_l2, LOW);
  digitalWrite(_r1, LOW);
  digitalWrite(_r2, LOW);
}

void Robest::forward() {
  digitalWrite(_l1, HIGH);
  digitalWrite(_l2, LOW);
  digitalWrite(_r1, HIGH);
  digitalWrite(_r2, LOW);
}

void Robest::backward() {
  digitalWrite(_l1, LOW);
  digitalWrite(_l2, HIGH);
  digitalWrite(_r1, LOW);
  digitalWrite(_r2, HIGH);
}

void Robest::right() {
  digitalWrite(_l1, LOW);
  digitalWrite(_l2, HIGH);
  digitalWrite(_r1, HIGH);
  digitalWrite(_r2, LOW);
}

void Robest::left() {
  digitalWrite(_l1, HIGH);
  digitalWrite(_l2, LOW);
  digitalWrite(_r1, LOW);
  digitalWrite(_r2, HIGH);
}

void Robest::testRun() {
  if (pass == true) {
    setSpeed(125);
    forward();
    delay(1000);
    stop();
    delay(1000);
    backward();
    delay(1000);
    stop();
    delay(1000);
    right();
    delay(1000);
    stop();
    delay(1000);
    left();
    delay(1000);
    stop();
    delay(1000);
  }
}

void Robest::checkBat(int OPT) {
  if (OPT == 1) {
    BatteryRead = analogRead(A0);
    BatteryValue = BatteryRead * (5.0 / 1023.0);
    if (BatteryValue > 2.0) {
      pass = true;
    } else {
      pass = false;
    }
  } else if (OPT == 0) {
    pass = true;
  }
}

void Robest::autoRunBT() {
  if (pass == true) {
    if (Serial.available()) {
      data = Serial.read();
      if (data == 'q') {
        int slider1val = Serial.parseInt();
        setSpeed(slider1val);
      } else if (data == 'W') {
        forward();
      } else if (data == 'S') {
        backward();
      } else if (data == 'A') {
        left();
      } else if (data == 'D') {
        right();
      } else if (data == 's') {
        stop();
      } else if (data == 'L') {
        digitalWrite(13, 1);
      } else if (data == 'l') {
        digitalWrite(13, 0);
      } else if (data == 'Y') {
        digitalWrite(12, 1);
      } else if (data == 'y') {
        digitalWrite(12, 0);
      } else if (data == 'P') {
        digitalWrite(7, 1);
      } else if (data == 'p') {
        digitalWrite(7, 0);
      } else if (data == 'R') {
        int RedVal = Serial.parseInt();
        analogWrite(3, RedVal);
      } else if (data == 'G') {
        int GreenVal = Serial.parseInt();
        analogWrite(10, GreenVal);
      } else if (data == 'B') {
        int BlueVal = Serial.parseInt();
        analogWrite(11, BlueVal);
      } else if (data == 'E') {
        digitalWrite(8, 1);
      } else if (data == 'e') {
        digitalWrite(8, 0);
      }
    }
  }
}