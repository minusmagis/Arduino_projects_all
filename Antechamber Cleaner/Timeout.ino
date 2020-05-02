#include "Header_file.h"

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
#define interval 60000           // interval at which to blink (milliseconds)

boolean Time_out(boolean reset = false){
  unsigned long currentMillis = millis();
  if(reset == true){
    previousMillis = currentMillis;
    #if defined debug
    Serial.println("timer reset");
    #endif
  }
  else if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.println("Timeout what?");
    return true;
  }
  else {
    return false;
  }
}
