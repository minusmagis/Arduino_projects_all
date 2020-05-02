#include <VarSpeedServo.h>

VarSpeedServo myservo;

void setup() 
{ 
  myservo.attach(11,1000,2500);
  Serial.begin(250000);
} 

void loop() {
//  float re = 50;
  myservo.slowmove(120,10);
  myservo.slowmove(0,10);
//  for(int i = 1000; i<=2500;i = i+re){
//  myservo.writeMicroseconds(i);  // set servo to mid-point
//  Serial.println(i);
//  delay(500);
//  }
//  for(int i = 2500; i>=1000;i = i-re){
//  myservo.writeMicroseconds(i);  // set servo to mid-point
//  Serial.println(i);
//  delay(500);
//  }
} 
