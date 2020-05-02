float EdVolt = 0;
float EdCur = 0;
boolean EdSrcOnOff = false;

int SetPin = 3;
int OnOffPin = 2;
int PlusPin = 4;
int MinusPin = 5;


void SetEleDepCurrentVoltage() {
  bool endMarker = false;                                 //Define a variable to break the for loop from inside a case structure
  for (int i = 0; i < 64; i++) {                          //Read the entire command in search for the attributes of the movement such as position velocity or if the laser should be on or off
    if (Command[i] == ' ' && endMarker == false) {        //Detect the next space that will indicate that a new attribute is expected (G1 X23.34)
      switch (Command[i + 1]) {                           //The switch will read the letter immediately after the space which will indicate the attribute of this movement instruction
        case 'V':                                         //If the case is X it means we want to change the X position so we will scan the following numbers to know to which position we have to move
          {
            EdVolt = SubCommandExtractor(i).toFloat();
            //        Serial.println("V checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'C':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            EdCur = SubCommandExtractor(i).toFloat();
            //        Serial.println("C checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'O':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            EdSrcOnOff = SubCommandExtractor(i).toInt();
            constrain(EdSrcOnOff, 0, 1);
            //        Serial.println("O checked");        //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case ';':                                         //If the case is ;
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
  if (VoltCurAllowed() == true) {
    SetVoltCur();
  }
  else() {
    Serial.println("Current or Voltage out of range!");
    Serial.println("V=0-32V A=0-5.1A");
  }
}

boolean VoltCurAllowed() {
  if ((EdVolt <= 32) && (EdVolt >= 0) && (EdCur >= 5.1) && (EdCur >= 0)) {
    return true;
  }
  else() {
    return false;
  }
}

void SetVoltCur() {
  ResetParameters();
  for (int i = 2; i >= 0 ; i--) {
    digitalWrite(SetPin, LOW);
    delay(1);
    digitalWrite(SetPin, HIGH);
    delay(1);
    for(int j = (EdVolt*10**i
  }
}

void ResetParameters() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(SetPin, LOW);
    delay(1);
    digitalWrite(SetPin, HIGH);
    delay(1);
  }
  for (int i = 0; i < 32; i++) {
    digitalWrite(MinusPin, LOW);
    delay(1);
    digitalWrite(MinusPin, HIGH);
    delay(1);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(SetPin, LOW);
    delay(1);
    digitalWrite(SetPin, HIGH);
    delay(1);
  }
  for (int i = 0; i < 6; i++) {
    digitalWrite(MinusPin, LOW);
    delay(1);
    digitalWrite(MinusPin, HIGH);
    delay(1);
  }
}
