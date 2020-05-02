float PosZ = 0;
float Feedrate = 1000;
float currentPosZ = 115;                   //The values at which the servos naturally start
extern boolean AbsolutePos;
extern boolean homez;


void MovingCommand() {
  if (homez == 1) {
    bool endMarker = false;                                 //Define a variable to break the for loop from inside a case structure
    if (AbsolutePos == false) {

      PosZ = 0; //Reinitialize the value of desired position before reading the new desired value

    }
    else {
      PosZ = 0; //Reinitialize the value of desired position before reading the new desired value
    }
    for (int i = 0; i < 64; i++) {                          //Read the entire command in search for the attributes of the movement such as position velocity or if the laser should be on or off
      if (Command[i] == ' ' && endMarker == false) {        //Detect the next space that will indicate that a new attribute is expected (G1 X23.34)
        switch (Command[i + 1]) {                           //The switch will read the letter immediately after the space which will indicate the attribute of this movement instruction                                       //Break the loop to continue looking for other attributes

          case 'Z':                                         //If the case is Z it means we want to change the Z position so we will scan the following numbers to know to which position we have to move
            {
              PosZ = SubCommandExtractor(i).toFloat();
              //        Serial.println("Z checked");                //For development purposes
            }
            break;                                           //Break the loop to continue looking for other attributes

          case 'F':                                         //If the case is F it means we want to change the feedrate so we will scan the following numbers to know to which position we have to move
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
    if (PositionAllowed() == true) {
      SetSteppersMovement();
    }
    else {
      Serial.println("Coordinate out of range!");
    }
  }
  else {
    Serial.println("Home First");
  }
}

