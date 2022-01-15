// Jitulex //
/* This is an example for the Robest Rover motor control board.
Use pins 5, 4, 2, 6 
pin number 9 for speed
*/

#include "Robest.h"  //include the Robest library.

//define the pins at which the motor controller is connected.
//Goes in the sequence of (R1, R2, L1, L2, SPD).
Robest robest(5, 4, 2, 6, 9); //Version 0 for Robest l293d 
//Robest robest(4, 5, 6, 7, 9); //Version 1 for Robest l298n

void setup() {
//initialize Robest and define the Baud rate for BT communication.(For V0 and V0 its "9600").
robest.init(9600);
//When Servos are disabled, the Slider is driven by PWM
robest.enableServo1(1);
robest.enableServo2(1);
robest.enableServo3(1);
}
void loop() {
robest.checkBat(1);
robest.autoRunBT();
}
