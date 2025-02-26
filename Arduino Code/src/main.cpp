#include <Arduino.h>
#include <SevSegShift.h>


#define SHIFT_PIN_DS   5/* Data input PIN */
#define SHIFT_PIN_STCP 4/* Shift Register Storage PIN */
#define SHIFT_PIN_SHCP 3/* Shift Register Shift PIN */

SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP); //Instantiate a seven segment controller object (with Shift Register functionality)
long Time=10000;
int Lastpressed=0;

void setup(){
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

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
int timetosec(long time){
  int output;
  output=time/6000;
  output=output*100;
  output=output+time/100%60;
  return output;
}
bool checkchange(){
  if (Pee==true){

  }

}

void loop() {
  Time--;
  if (digitalRead(9)==false){
    if (Lastpressed != 1){
      Time=6000;
    }
    else{
      Time=Time+15;
    }
    Lastpressed=1;
  }
  if (digitalRead(10)==false){
    if (Lastpressed != 1){
      Time=6000;
    }
    else{
      Time=Time+15;
    }
    Lastpressed=1;
  }
  if (digitalRead(11)==false){
    if (Lastpressed != 2){
      Time=30000;
    }
    else{
      Time=Time+45;
    }
    Lastpressed=2;
  }
  if (digitalRead(12)==false){
      if (Lastpressed != 3){
        Time=60000;
      }
      else{
        Time=Time+90;
      }
      Lastpressed=3;
  }


  if (Time <1){
    Lastpressed=0;
    Time=0;
  }
  sevseg.setNumber(timetosec(Time), 1);
  sevseg.refreshDisplay(); // Must run repeatedly
}
void setTime(){
  Time=10000;
}