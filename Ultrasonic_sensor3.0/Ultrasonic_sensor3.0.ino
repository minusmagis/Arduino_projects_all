/* HC-SR04 Sensor 
   The circuit:
  * VCC connection of the sensor attached to +5V
  * GND connection of the sensor attached to ground
  * TRIG connection of the sensor attached to digital pins
  * ECHO connection of the sensor attached to digital pins
 */
#include <Servo.h> 

int trigPin1 = 2;
int echoPin1 = 3;
int trigPin2 = A0;
int echoPin2 = A1;
int trigPin3 = 8;
int echoPin3 = 9;
int trigPin4 = 10;
int echoPin4 = 11;
int trigPin5 = 4;
int echoPin5 = 7;
int trigPin6 = 13;
int echoPin6 = 12;

unsigned long data = 0;

int n=0;
int m=0;
Servo myservo;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
    myservo.attach(6);
  Serial.begin(9600);
  myservo.write(40);

}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration,duration1,duration2,duration3,cm1, cm2, cm3, cm4, cm5 , cm6;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);

  delay(5);

   // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration2 = pulseIn(echoPin1, HIGH);

    delay(5);

   // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin1, OUTPUT);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration3 = pulseIn(echoPin1, HIGH);

  delay(5);

  // convert the time into a distance
  cm1 = ((duration1+duration2+duration3)/3) / 29 / 2;
  
 //   Serial.print(cm1, DEC);
 // Serial.print(" cm1  ");

  delay(10);
  


 pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
    pinMode(echoPin2, INPUT);
  duration1 = pulseIn(echoPin2, HIGH);

    delay(5);

   pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
    pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);

    delay(5);

   pinMode(trigPin2, OUTPUT);
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
    pinMode(echoPin2, INPUT);
  duration3 = pulseIn(echoPin2, HIGH);
  
  delay(5);
  
    cm2 = ((duration1+duration2+duration3)/3) / 29 / 2;

//  Serial.print(cm2, DEC);
// Serial.print(" cm2  ");

  

  
  delay(10);
  
    pinMode(trigPin3, OUTPUT);
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  
    pinMode(echoPin3, INPUT);
  duration = pulseIn(echoPin3, HIGH);
    cm3 = duration / 29 / 2;

//  Serial.print(cm3, DEC);
//  Serial.print(" cm3  ");

  
  delay(10);
  
  
    pinMode(trigPin4, OUTPUT);
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  
    pinMode(echoPin4, INPUT);
  duration = pulseIn(echoPin4, HIGH);
    cm4 = duration / 29 / 2;

 // Serial.print(cm4, DEC);
 // Serial.print(" cm4  ");

  
  delay(10);

    pinMode(trigPin5, OUTPUT);
  digitalWrite(trigPin5, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin5, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin5, LOW);
  
    pinMode(echoPin5, INPUT);
  duration = pulseIn(echoPin5, HIGH);
    cm5 = duration / 29 / 2;

 // Serial.print(cm5, DEC);
//  Serial.print(" cm5  ");

  
  delay(10);

    pinMode(trigPin6, OUTPUT);
  digitalWrite(trigPin6, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin6, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin6, LOW);
  
    pinMode(echoPin6, INPUT);
  duration = pulseIn(echoPin6, HIGH);
    cm6 = duration / 29 / 2;

  Serial.print(cm1,DEC);
  Serial.print(",");
  Serial.print(cm2,DEC);
    Serial.print(",");
  Serial.print(cm3,DEC);
    Serial.print(",");
  Serial.print(cm4,DEC);
    Serial.print(",");
  Serial.print(cm5,DEC);
    Serial.print(",");
  Serial.println(cm6,DEC);
Serial.print(":");
  delay(100);
 // Serial.println(" cm6  ");

  
  delay(10);
/*m=5+m;
  if (m<90){
    myservo.write(n);
    n=5+n;
    delay(500);
      }
  else if (m<180){
    myservo.write(n);
    n=n-5;
    delay(500);
    }
  else if (m>=180){
    m=0;
    n=0;
  }*/
}

