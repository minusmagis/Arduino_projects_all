#include <SpeedyStepper.h>
#define debug 1

const int STEPPERS_ENABLE_PIN = 8;
const int MOTOR_Z_STEP_PIN = 2;
const int MOTOR_Z_DIR_PIN = 5;
const int LIMIT_SWITCH_Z_PIN = 11;

extern float Zstepsmm;
extern int Zmmss;


SpeedyStepper stepperZ;

void setup() {
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);                  // Set the enable pin as an output
  pinMode(LIMIT_SWITCH_Z_PIN, INPUT_PULLUP);
  
  stepperZ.connectToPins(MOTOR_Z_STEP_PIN, MOTOR_Z_DIR_PIN);        //Initialize the motors
  stepperZ.setStepsPerMillimeter(Zstepsmm);
  stepperZ.setAccelerationInMillimetersPerSecondPerSecond(Zmmss);

  digitalWrite(STEPPERS_ENABLE_PIN, LOW);                // Enable the steppers
  #if defined debug
  Serial.begin(250000);                                    // Begin Serial communication
  #endif
  StartCode();                                           // Send the startcode
}

void loop() {
  GcodeCommandReceive();
  GcodeToInstructions();
}
