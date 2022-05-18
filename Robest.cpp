#include "Robest.h"

Robest::Robest(int r1, int r2, int l1, int l2, int spd) {
  _l1 = l1;
  _l2 = l2;
  _r1 = r1;
  _r2 = r2;
  _spd = spd;
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(spd, OUTPUT);
}


void Robest::init(unsigned long baud) {
  Serial.begin(baud);
}

void Robest::Read(){
  if(Serial.available()){
    data = Serial.read();
    if(data == 'U'){
      OASEN = 1;
    }
    else if(data == 'u'){
      OASEN = 0;
    }
    else if(data == 'O'){
      minOASdistance = Serial.parseInt();
      constrain(minOASdistance,5,50);
    }
  }
}

void Robest::setSpeed(int SPD) {
 // s1.detach();
 // s2.detach();
 // s3.detach();
  analogWrite(_spd, SPD);
}

void Robest::OASinit(int ECHO, int TRIG){
  echo = ECHO;
  trig = TRIG;
 pinMode(echo, INPUT);
 pinMode(trig, OUTPUT);
 OASisinitiated = 1;
}

void Robest::OAS(){
  if(OASEN == 1 && OASisinitiated == 1){
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance = duration * 0.034 / 2;
  //Serial.println(distance);
  if(distance < minOASdistance){
    obstacle = 1;
    fwd = 0;
    for(x = 0; x<=1; x++){
      stop();
    }
  }
  else if(distance > minOASdistance){
    obstacle = 0;
    fwd = 1;
    x=0;
  }
 }
 else if(OASEN == 0){
   obstacle = 0;
   fwd = 1;
 }
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
    BattPercentage = ((BatteryValue-2.0)*100) / (4.2-2.0);
    constrain(BattPercentage,0,100);
    if (BatteryValue > 2.0) {
      pass = true;
    } else {
      pass = false;
    }
  } else if (OPT == 0) {
    pass = true;
  }
}
void Robest::enableServo1(bool on1){
  if(on1 == 1){
    S1 = 0;
    s1.attach(3);
  }
  else if(on1 == 0){
    S1 = 1;
    s1.detach();
  }
}
void Robest::enableServo2(bool on2){
  if(on2 == 1){
    S2 = 0;
    s2.attach(10);
  }
  else if(on2 == 0){
    S2 = 1;
    s2.detach();
  }
}
void Robest::enableServo3(bool on3){
  if(on3 == 1){
    S3 = 0;
    s3.attach(11);
  }
  else if(on3 == 0){
    S3 = 1;
    s3.detach();
  }
}
void Robest::run(){
  OAS();
   if (pass == true) {
      if (data == 'q') {
        int slider1val = Serial.parseInt();
        setSpeed(slider1val);
      } else if (data == 'W') {
        if(fwd == 1){
        forward();
        }
      } else if (data == 'S') {
        backward();
      } else if (data == 'A') {
        left();
      } else if (data == 'D') {
        right();
      } else if (data == 's') {
        stop();
      }
      else if (data == 'M') {
        Serial.println(BattPercentage,0);
      }
      light();
      horn();
      PWM0();
      PWM1();
      PWM2();
    }
}
void Robest::autoRunBT() {
  Read();
  run();
}
void Robest::lineFollower(){
  if(digitalRead(13) == 0 && digitalRead(12) == 0){
    forward();
  }
  else if(digitalRead(13) == 1 && digitalRead(12) == 0){
    left();
  }
  else if(digitalRead(13) == 0 && digitalRead(12) == 1){
    right();
  }
  else if(digitalRead(13) == 1 && digitalRead(12) == 1){
    stop();
  }
}
void Robest::lightinit(bool LIGHTATTACH){
 if(LIGHTATTACH == 1){
  pinMode(13,OUTPUT);
  lightattach = 1;
 }
 else{
  lightattach = 0;
 }
}
void Robest::horninit(bool HORNATTACH){
  if(HORNATTACH == 1){
  pinMode(12,OUTPUT);
  hornattach = 1;
 }
 else{
  hornattach = 0;
 }
}
void Robest::PWM0init(bool PWM0ATTACH){
 if(PWM0ATTACH == 1){
  pinMode(3,OUTPUT);
  pwm0attach = 1;
 }
 else{
  pwm0attach = 0;
 }
}
void Robest::PWM1init(bool PWM1ATTACH){
 if(PWM1ATTACH == 1){
  pinMode(10,OUTPUT);
  pwm1attach = 1;
 }
 else{
  pwm1attach = 0;
 }
}
void Robest::PWM2init(bool PWM2ATTACH){
 if(PWM2ATTACH == 1){
  pinMode(11,OUTPUT);
  pwm2attach = 1;
 }
 else{
  pwm2attach = 0;
 }
}
void Robest::light(){
 if(lightattach == 1){
 if (data == 'L') {
   digitalWrite(13, 1);
  } else if (data == 'l') {
   digitalWrite(13, 0);
      }
 }
 else{
 }
}
void Robest::horn(){
 if(hornattach == 1){
 if (data == 'Y') {
   digitalWrite(12, 1);
  } else if (data == 'y') {
   digitalWrite(12, 0);
      }
 }
 else{

 }
}
void Robest::PWM0(){
  if(pwm0attach == 1){
      if (data == 'R') {
        RedVal = Serial.parseInt();
        if(S1 == 1){
        analogWrite(3, RedVal);
        }
        else if(S1 == 0){
          constrain(RedVal,0,180);
          s2.write(RedVal);
        }
      }

  }
}
void Robest::PWM1(){
  if(pwm1attach == 1){
        if (data == 'G') {
        GreenVal = Serial.parseInt();
        if(S2 == 1){
        analogWrite(10, GreenVal);}
        else if(S2 == 0){
          constrain(GreenVal,0,180);
          s2.write(GreenVal);}
      }

  }
}
void Robest::PWM2(){
  if(pwm2attach == 1){
        if (data == 'B') {
        BlueVal = Serial.parseInt();
        if(S3 == 1){
        analogWrite(11, BlueVal);}
        else if(S3 == 0){
          constrain(BlueVal,0,180);
          s3.write(BlueVal);
        }
  }
 }
}
void Robest::IOinit(int pin, char BTVAL, char btval){
  pinMode(pin,OUTPUT);
  if(data == BTVAL){
    digitalWrite(pin,1);
  }
  else if(data == btval){
    digitalWrite(pin,0);
  }
}
int Robest::getSliderVal1(){
  return(int)(RedVal);
}
int Robest::getSliderVal2(){
  return(int)(GreenVal);
}
int Robest::getSliderVal3(){
  return(int)(BlueVal);
}
char Robest::getdata(){
  return(char)(data);
}
float Robest::BatteryLevel(){
  return(float)(BattPercentage);
}
