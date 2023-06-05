//main file that runs when program is called.

#include <Servo.h>
#include "motors.h"
#include "servo.h"
#include "ultrasonic.h"
#include <NewPing.h>

int go = 1; //bool to track status of buggy motion
int i = 0; //bool to track number of turns made
int j = 0; //bool that decides whether buggy should turn in response to side sensor measurements.
int cm1 = 0; //cm1 for distance of Front sensor, cm2 for distance of Side sensor
int cm2 = 0;
int dist = 0; //variable to keep the previous measurement of cm2 for distance calculation

NewPing sonar(trigPinF, echoPinF, max_dist);

void setup(){
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
  pinMode(trigPinS, OUTPUT);
  pinMode(echoPinS, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  servo1.attach(11);

  Serial.begin(9600);
}

long readPing(){
  int distance = sonar.ping_cm();
  return distance;
}

void loop() {

  cm1 = ultrasound(trigPinF, echoPinF);//front sensor
  cm2 = ultrasound(trigPinS, echoPinS); //side sensor
  

  Serial.print(cm2);
  Serial.println(" cm2");


  if (cm1 >= 10){
    i = 0;
    go = 1;
    forward();
    delay(50);
    dist = ultrasound(trigPinS, echoPinS);

    if (cm2 > 30 && j == 0){ //if there is a path to the right, and buggy is allowed to turn i.e. j == 0
      j = 1; //This is to ensure buggy does not turn repeatedly.       
      delay(500);//delay to ensure buggy clears the wall to its side before turning.
      clockwise();
    }
    if (((cm2 - dist) > 0 || cm2 < 5 ) && j == 0){
      adjust_anticlock(); //if buggy is moving towards the wall and is allowed to turn, make a anticlocwise adjustment
    }
    else if ((cm2 - dist) < 0 && j == 0){
      adjust_clock(); //if buggy is away from wall and is allowed to turn, make a clocwise adjustment
    }
     else if (cm2 < 20){
      j = 0;//Enables buggy to turn only if it sensed a wall previously. 
    }
  } 
  else if (cm1 < 10){
    j = 0;
    go = 0;
    ++i;
    freeze(); //Stop 
      if (i == 1){
        anticlockwise(); //Turn anticlockwise. 
        delay(100);
      }
      else if (i == 2){
        anticlockwise(); //Go back the way it came.
        i = 0;
        delay(100);
      }
  }
}
