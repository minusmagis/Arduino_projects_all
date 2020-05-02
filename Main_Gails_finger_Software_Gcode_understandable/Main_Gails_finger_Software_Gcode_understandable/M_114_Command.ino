extern float currentPosZ;

void GetCurrentPosition(){                    //Print the current coordinates stored in currentPosXZ[] variable in the following form: X:0.00 Z:0.00
  Serial.print("Homed = ");
  Serial.print(homez);
  Serial.print(" Z:");
  Serial.println(currentPosZ);
  
}
