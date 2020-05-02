#include "Header_file.h"

//-------------------Definition of the possible commands (this can be expanded at will)------------------



unsigned long previousMillisread = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;

boolean reading_clean = false;
boolean reading_refill = false;
boolean cancel_cross_command = false;

int clean_button_state = LOW;
int refill_button_state = LOW;

int clean_button_counter = 0;
int refill_button_counter = 0;

int clean_button_last_state = LOW;
int refill_button_last_state = LOW;

int Button_Read() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisread >= Debounce_Interval) {
    clean_button_state = digitalRead(clean_button);
    refill_button_state = digitalRead(refill_button);
    previousMillisread = currentMillis;
  }

  if (clean_button_state != clean_button_last_state) {
    clean_button_counter++;
    clean_button_last_state = clean_button_state;
    previousMillis1 = currentMillis;
    reading_clean = true;
  }

  if (refill_button_state != refill_button_last_state) {
    refill_button_counter++;
    refill_button_last_state = refill_button_state;
    previousMillis2 = currentMillis;
    reading_refill = true;
  }

  if (currentMillis - previousMillis1 > Button_Interval && reading_clean == true) {
    reading_clean = false;
    //Serial.println("Resetting clean");
    if (clean_button_counter == 4) {
      clean_button_counter = 0;
      Serial.println("Clean Command");
      return Clean_Command;
    }
    else if (clean_button_counter == 8) {
      clean_button_counter = 0;
      Serial.println("Clean Half Cycles Command");
      return Clean_Half_Cycles_Command;
    }
    else if (clean_button_counter == 10) {
      clean_button_counter = 0;
      if (refill_button_counter == 10) {
        refill_button_counter = 0;
        Serial.println("Calibrate Command");
        cancel_cross_command = true;
        return Calibrate_Command;
      }
      else {
        Serial.println("Unknown Command");
        return Unknown_Command;
      }
    }
    else {
      Serial.println("Default clean");
      clean_button_counter = 0;
      if (cancel_cross_command == false) return Unknown_Command;
      cancel_cross_command = false;
    }
  }

  else if (currentMillis - previousMillis2 > Button_Interval && reading_refill == true) {
    reading_refill = false;
    //Serial.println("Resetting refill");
    if (refill_button_counter == 4) {
      refill_button_counter = 0;
      Serial.println("Refill Command");
      return Refill_Command;
    }
    else if  (refill_button_counter == 10) {
      refill_button_counter = 0;
      if (clean_button_counter == 10) {
        clean_button_counter = 0;
        Serial.println("Calibrate Command");
        cancel_cross_command = true;
        return Calibrate_Command;
      }
      else {
        Serial.println("Unknown Command");
        return Unknown_Command;
      }
    }
    else {
      Serial.println("Default refill");
      refill_button_counter = 0;
      if (cancel_cross_command == false) return Unknown_Command;
      cancel_cross_command = false;
    }
  }
  else {
    return Unknown_Command;
  }
}
