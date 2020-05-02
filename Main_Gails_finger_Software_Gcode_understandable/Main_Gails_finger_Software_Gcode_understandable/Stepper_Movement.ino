extern const int STEPPERS_ENABLE_PIN;
extern const int MOTOR_Z_STEP_PIN;
extern const int MOTOR_Z_DIR_PIN;
extern const int LIMIT_SWITCH_Z_PIN;
extern float currentPosZ;
extern int ZaxisRange;      

float Zstepsmm = 1777;                                       //Define the steps per mm of the z axis
float ZspeedinMMs = 5;                                     //Define the speed in mm/s for the z axis
int Zmmss = 15;                                            //Define the acceleration in mm/s^2 for the z axis

float ZStepsPerSecond = Zstepsmm*ZspeedinMMs;                                         //in steps per second (has to be calibrated)
float ZStepsPerSecondPerSecond = Zstepsmm*Zmmss;                                //in steps per second per second (has to be calibrated)

void MoveSteppers(float Zmove){
  int i = 0;
  ZStepsPerSecond = Feedrate*Zstepsmm*ZspeedinMMs/1000;
  long stepsZ = Zmove*Zstepsmm;
#if defined debug
  Serial.println(stepsZ);
#endif
  stepperZ.setSpeedInStepsPerSecond(ZStepsPerSecond);
  stepperZ.setAccelerationInStepsPerSecondPerSecond(ZStepsPerSecondPerSecond);
  stepperZ.setupRelativeMoveInSteps(stepsZ);
    while(!stepperZ.motionComplete())
  {
    stepperZ.processMovement();
    i++;
    if(i>100){
      //Serial.println("Moving...");
      if (digitalRead(LIMIT_SWITCH_Z_PIN) == LOW && (stepsZ >0)){
       currentPosZ = ZaxisRange;
        break; 
      }
      i = 0;
    }
  }
  Serial.println("Moved");
}
