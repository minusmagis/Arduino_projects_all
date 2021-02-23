// This script will make the pump rotate for a give amount of time to water the plants

// We need to include the definitions file to have all the definition names
#include "Definitions.h"

// Afterwards we use the methods of the SpeedyStepper methods to define the pump motor
SpeedyStepper PeristalticPump;

unsigned long YeldIntervalCounter = 0;


void Water_Plants()
{
  // We first need to enable the peristaltic pump motor to be able to move it
  digitalWrite(ENABLE_PIN, LOW);

  // Afterwards we set the motor speed and acceleration
  PeristalticPump.setSpeedInStepsPerSecond(PeristalticPump_Speed);
  PeristalticPump.setAccelerationInStepsPerSecondPerSecond(PeristalticPump_Acceleration);

  // We calculate the amount of steps the motor has to make to pump the desired volume
  unsigned long steps = PeristalticPump_Volume * VolumeToSteps;

  // Finally we move the motor and if we desire we serialprint a message
#ifdef SerialMessages
  Serial.println("Watering Plants");
#endif

  PeristalticPump.setupRelativeMoveInSteps(steps);

  while (!PeristalticPump.motionComplete())
  {
    if (YeldIntervalCounter > YeldInterval) {
      yield();
      YeldIntervalCounter = 0;
    }
    YeldIntervalCounter++;
    PeristalticPump.processMovement();       // this call moves themotor
  }
#ifdef SerialMessages
  Serial.println("Plants Watered");
#endif

  digitalWrite(ENABLE_PIN, HIGH);
}
