#include <Arduino.h>
#include <SevSegShift.h>


#define SHIFT_PIN_DS   5/* Data input PIN */
#define SHIFT_PIN_STCP 4/* Shift Register Storage PIN */
#define SHIFT_PIN_SHCP 3/* Shift Register Shift PIN */

SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP); //Instantiate a seven segment controller object (with Shift Register functionality)
volatile int Time=10000;
void setTime();

void setup(){
  pinMode(2, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);


  attachInterrupt(digitalPinToInterrupt(2), setTime, CHANGE);
  byte numDigits = 4;   
  byte digitPins[] = {1,4,5,8+6}; //Digits: 1,2,3,4 <--put one resistor (ex: 220 Ohms, or 330 Ohms, etc, on each digit pin)
  byte segmentPins[] = {2,6,8+4,8+2,8+1,3,8+5,8+3}; //Segments: A,B,C,D,E,F,G,Period

  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = true; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = true; // Use 'true' if your decimal point doesn't exist or isn't connected

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(45);  

}

void loop() {
  Time--;
  if (Time <1){
    Time=0;
  }
  sevseg.setNumber(Time/100, 1);
  sevseg.refreshDisplay(); // Must run repeatedly
}
void setTime(){
  Time=10000;
  if (analogRead(A0)!=LOW){
    Time=20000;
  }
  if (analogRead(A1)!=LOW){
    Time=30000;
  }
}