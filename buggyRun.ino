//main file that runs when program is called.

#include <Servo.h>
#include "motors.h"
#include "servo.h"
#include "ultrasonic.h"
#include <NewPing.h>

int go = 1;
int i = 0;
int cm = 0;

NewPing sonar(trigPinF, echoPinF, max_dist);

void setup(){
  pinMode(trigPinF, OUTPUT);
  pinMode(echoPinF, INPUT);
//  pinMode(trigPinSF, OUTPUT);
//  pinMode(echoPinSF, INPUT);
//  pinMode(trigPinSB, OUTPUT);
//  pinMode(echoPinSB, INPUT);

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

//  if (state == 1){
//    clockwise();
//  }
//  else if (state == 0){
//    anticlockwise();
//  }
//
//  delay(1000);
//
//  if (i % 2 == 0){
//    state = 1;
//  }
//  else {
//    state = 0;
//  }
//  i++;

  cm = ultrasound(trigPinF, echoPinF);

// cm = sonar.ping_cm();

  Serial.print(cm);
  Serial.println(" cm");


  if (cm >= 10){
    i = 0;
    go = 1;
    forward();
  }
  else if (cm < 10){
    go = 0;
    ++i;
    freeze();
    //calculate distance after turning.
      if (i == 1){
        clockwise();
      }
      else if (i == 2){
        anticlockwise();
        anticlockwise();
      }
      else if (i == 3){
        anticlockwise();
        i = 0;
      }
  }

//  if (go == 0){
//    compare(trigPinSF, echoPinSF, trigPinSB, echoPinSB);
//  }
}
