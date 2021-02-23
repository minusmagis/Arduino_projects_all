/*
   This code is used to control a self watering grow station that controls the ambient temperature and humidity as well as the soil temperature and moisture levels.
   Author: minusmagis
   Last update: 09/01/2021
*/

// First we include all the needed libraries and header files
#include "DHTesp.h"
#include "Definitions.h"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SpeedyStepper.h>

unsigned long lastMsg = 0;
unsigned long lastUpdate = 0;

// On the setup we initialize all the comunications needed for the software to work
void setup()
{
StartCode();
}

void loop()
{
  unsigned long messageNow = millis();
  if (messageNow - lastMsg > MessageReceiveDelay) {
    lastMsg = messageNow;
    FastUpdate();
  }

  unsigned long StatusNow = millis();
  if (StatusNow - lastUpdate > StatusUpdateDelay) {
    lastUpdate = StatusNow;
    Get_Conditions();
  }
}
