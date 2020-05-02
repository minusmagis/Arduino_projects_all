extern float PosZ;
extern float Feedrate ;
extern float currentPosZ;                   //The values at which the servos naturally start

int MeasuringInterval = 1000;              //Capacitance measurement interval in steps to prevent the movement from being too slow

extern float ZStepsPerSecond;
extern float ZStepsPerSecondPerSecond;
extern int Zmmss;
extern float Zstepsmm ;                                       //Define the steps per mm of the z axis
extern float ZspeedinMMs;                                     //Define the speed in mm/s for the z axis
extern int Zmmss;                                            //Define the acceleration in mm/s^2 for the z axis
extern boolean homez;
extern int ZaxisRange;                                  //Declare the range of the z axis (in mm) from zero to the value

void ApproachSample() {
  if (homez == 1) {
    bool endMarker = false;                                 //Define a variable to break the for loop from inside a case structure
    for (int i = 0; i < 64; i++) {                          //Read the entire command in search for the attributes of the movement such as position velocity or if the laser should be on or off
      if (Command[i] == ' ' && endMarker == false) {        //Detect the next space that will indicate that a new attribute is expected (G1 X23.34)
        switch (Command[i + 1]) {                           //The switch will read the letter immediately after the space which will indicate the attribute of this movement instruction                                       //Break the loop to continue looking for other attributes

          case 'F':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
            {
              Feedrate = SubCommandExtractor(i).toFloat();
              //        Serial.println("F checked");                //For development purposes
            }
            break;

          case ';':                                         //If the case is ;
            endMarker = true;                               //Set the endmarker flag to true to stop the loop
            break;

          case '\n':                                         //If the case is ;
            endMarker = true;                               //Set the endmarker flag to true to stop the loop
            break;

          case '\0':                                         //If the case is ;
            endMarker = true;                               //Set the endmarker flag to true to stop the loop
            break;

          case ' ':                                         //If the case is ;
            endMarker = true;                               //Set the endmarker flag to true to stop the loop
            break;

          default:
            {
              UnknownCommand();                                 //In the case of anything else, send: Unknown Command
              endMarker = true;                                 //And break the for loop that was looking for other attributes of the G command
            }
            break;
        }
      }
      else if (endMarker == true) {
        break;
      }
    }
    Approach();
  }
  else {
    Serial.println("Home First");
  }
}

void Approach() {
  capacitiveReset();
  if (ZspeedinMMs >=1){
  ZspeedinMMs = 1;
  }
  boolean sucAp = 0;
  long i = 0;
  unsigned int j = 0;
  int k = 0;
  long offsetHome = ((ZaxisRange - 5) - currentPosZ) * Zstepsmm;
  ZStepsPerSecond = Feedrate * Zstepsmm * ZspeedinMMs / 1000;
  long stepsZ = -currentPosZ * Zstepsmm;
#if defined debug
  Serial.println(stepsZ);
#endif
  stepperZ.setSpeedInStepsPerSecond(ZStepsPerSecond);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(ZStepsPerSecondPerSecond);
  stepperZ.setupRelativeMoveInSteps(stepsZ);
  while (!stepperZ.motionComplete())
  {
    stepperZ.processMovement();
    i = stepperZ.getCurrentPositionInSteps();
    j++;
    k++;
    if (j > 30000)
    {
      Serial.print("Approaching...");
      Serial.println(i);

      j = 0;
    }
//#if defined debug
//    Serial.println("Current Step");
//    Serial.println(i);
//    Serial.println("Limit Switch");
//    Serial.println(digitalRead(LIMIT_SWITCH_Z_PIN));
//#endif
    if (k > MeasuringInterval) {
     k = 0;
      if (capacitiveValue()) {
        sucAp = 1;
        Serial.println("Successful approach");
        break;
      }
    }
  }
#if defined debug
  Serial.println("Total Steps");
  Serial.println(i);
#endif
  currentPosZ = ZaxisRange + (i / Zstepsmm);
  if (sucAp == 0) {
    Serial.println("Limit Reached, unsuccesful approach");

  }

}


