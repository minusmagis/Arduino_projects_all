extern float PosZ;                          //Define external variaables
extern boolean AbsolutePos; 
const float ZhomingSpeedInMMPerSec = 10.0; 
const float ZmaxHomingDistanceInMM = 200;   // The axis is max 300 mm long so homing for a longer distance does not make sense
const int directionTowardHome = 1;        // Direction to move toward limit switch: 1 goes positive direction, -1 backward
extern const int LIMIT_SWITCH_Z_PIN;
boolean homez = false;
extern float currentPosZ;                           //Declare external variables for use in this part of the script

void Home() {

  AbsolutePos = true;                             //Set the absolute positioning to true to be able to go to the home position accurately (NOTE THAT IF ON RELATIVE MODE HOMING WILL OVERRIDE TO ABSOLUTE MODE)
  PosZ = 115;                                   //Set the position to the homing position and home the steppers
  currentPosZ = 115;
  homez = stepperZ.moveToHomeInMillimeters(directionTowardHome, ZhomingSpeedInMMPerSec, ZmaxHomingDistanceInMM, LIMIT_SWITCH_Z_PIN);
  //delay(500);
  if (homez){
  Serial.println("Homed");  
  }
  else{
  Serial.println("Failed");
  Serial.print(homez);
  }
}
