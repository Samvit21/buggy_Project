//header file dedicated to ultrasonic sensor code.

#define trigPinF A0
#define echoPinF A1
const int max_dist = 100;
//const int trigPinSF = 3;
//const int echoPinSF = 4;
//const int trigPinSB = 5;
//const int echoPinSB = 6;

long duration = 0;

//calculates distance from buggy to obstacle in cm.
long ultrasound(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echoPinF, HIGH);
  return (duration*0.034)/2.0;
}

//void compare(int trigPinSF, int echoPinSF, int trigPinSB, int echoPinSB){
//  
//  //determines whether buggy is paralled to wall by comparing distance from front and back of buggy.
//  long dist;
//  dist = round(ultrasound(trigPinSF, echoPinSF) - ultrasound(trigPinSB, echoPinSB));
//  //adjust position if buggy is not parallel.
//  if (dist > 0.5){
//    adjust_anticlock();
//  }
//  else if (dist < -0.5){
//    adjust_clock();
//  }
//}
