/*Example sketch to control a stepper motor with DRV8825 stepper motor driver and Arduino. More info: https://www.makerguides.com */
//Define stepper motor connections and steps per revolution
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 6400
#define delay1  200
#define delay2  100
#define delay3  50

void setup()
{
  //Set pins as output
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void loop()
{
  //Set motor direction clockwise
  digitalWrite(dirPin, HIGH);
  // Spin motor 1 revolution slowly
  for(int i = 0; i < stepsPerRevolution; i++)
  {
    digitalWrite(stepPin, HIGH); //These four lines result in 1 step
    delayMicroseconds(delay1);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delay1);
  }
  delay(1000); // Wait a second
  
  //Set motor direction counterclockwise
  digitalWrite(dirPin, LOW);
  //Spin motor 1 revolution quickly 
  for(int i = 0; i < stepsPerRevolution; i++)
  {
    digitalWrite(stepPin, HIGH); //These four lines result in 1 step
    delayMicroseconds(delay2);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delay2);
  }
  delay(1000); // Wait a second
    //Set motor direction clockwise
  digitalWrite(dirPin, HIGH);
  // Spin motor 5 revolutions fast
  for(int i = 0; i < 5*stepsPerRevolution; i++)
  {
    digitalWrite(stepPin, HIGH); //These four lines result in 1 step
    delayMicroseconds(delay3);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delay3);
  }
  delay(1000); // Wait a second
    //Set motor direction counterclockwise
  digitalWrite(dirPin, LOW);
  //Spin motor 5 revolutions fast 
  for(int i = 0; i < 5*stepsPerRevolution; i++)
  {
    digitalWrite(stepPin, HIGH); //These four lines result in 1 step
    delayMicroseconds(delay3);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delay3);
  }
  delay(1000); // Wait a second
}
