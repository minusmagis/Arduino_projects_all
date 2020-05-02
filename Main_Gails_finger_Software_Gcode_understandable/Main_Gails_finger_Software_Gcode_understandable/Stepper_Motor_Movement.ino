extern boolean AbsolutePos;
extern float currentPosZ;                           //Declare external variables for use in this part of the script
extern float PosZ;
extern float Feedrate;
extern boolean AllowedPosition;
int ZaxisRange = 115;                                  //Declare the range of the z axis (in mm) from zero to the value


void SetSteppersMovement() {                             //Function for moving the steppers around sinchronously
  //  Serial.println("Move Steppers Checked");           //For Development purposes
  float Zmove = 0;                               //This variable stores the direction vector towards which we want the XZ carriage to move
  if (AbsolutePos == true)                               //If the XZ carriage is in absolute position movement calculate the coordinates for the moving vector
  {
    //Serial.println("Absolute Check");
                                                  //Scan the PosZ and calculate the distance between the desired position and the current position in each axis
      Zmove = PosZ - currentPosZ;                  //Store the value of the direction vector
    
//            Serial.print(" Movement in the z position: ");
//            Serial.println(Zmove);                   //For development purposes
  }

  else {                                       //If the arm is in relative position movement use the coordinates as the moving vector
    
      //Serial.println("Relative Check");
                  //Scan the PosZ and set it to be the direction vector since the XZ carriage is in relative position movement
        Zmove = PosZ;                         //Store the value of the direction vector
      
      //        Serial.print(" Movement in the z position: ");
      //        Serial.println(Zmove);                   //For development purposes
    
  }
  MoveSteppers(Zmove);
  currentPosZ = PosZ;
}

boolean PositionAllowed() {                                 //Check if the position to which the command tells the carriage to move is within the carriage range, and if so return true, otherwise return false
  if (AbsolutePos == true) {
    if ( (0 <= PosZ) && ( PosZ <= ZaxisRange)) {    //If the desired position is whithin this range the movement is allowed
      //      Serial.println("Whithin range Abs");                                                        //For development purposes
      return true;

    }
    else {
      //      Serial.println("Out of range Abs");                           //For development purposes
      return false;

    }
  }
  else {
    float Zfinal = 0;                                  //Create a variable that will hold the final position to prevent moving beyond the set boundaries of the arm in relative mode
                              //Set the final position to the sum of the current position plus the amount we want to move in each direction
      Zfinal = PosZ + currentPosZ;
    
    if ( (0 <= Zfinal) && ( Zfinal <= ZaxisRange)) {  //If the final calculated position is whithin this range the movement is allowed
      //      Serial.println("Whithin range rel");                           //For development purposes
      return true;

    }
    else {
      //      Serial.println("Out of range rel");                           //For development purposes
      return false;

    }
  }
}
