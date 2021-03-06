#include <CapacitiveSensor.h>

long capacitiveThreshold = 50;
int average = 0;
const byte samples = 20;

int arrays[samples];
int nextIndex = 0;
int l = 0;
int m = 0;
/*
   CapitiveSense Library Demo Sketch
   Paul Badger 2008
   Uses a high value resistor e.g. 10 megohm between send pin and receive pin
   Resistor effects sensitivity, experiment with values, 50 kilohm - 50 megohm. Larger resistor values yield larger sensor values.
   Receive pin is the sensor pin - try different amounts of foil/metal on this pin
   Best results are obtained if sensor foil and wire is covered with an insulator such as paper or plastic sheet
*/


CapacitiveSensor   cs_12_13 = CapacitiveSensor(12, 13);       // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil

void capacitiveReset() {
  average = 0;
  for (int i = 0; i < samples; i++) {
    arrays[i] = 0;
  }
  for (int h = 0; h < samples*50; h++) {
    long total1 =  cs_12_13.capacitiveSensor(100);
    arrays[nextIndex] =  total1;
    //The "%" is the modulo operator. "a = b%c" gives you the remainder of dividing b by c
    nextIndex = (nextIndex + 1) % samples;
    m = nextIndex;
    for (int i = 0; i < samples; i++)
    {
      average = average + arrays[i];
    }
    average = average / samples;
  }
  capacitiveThreshold = average + 20;
}

boolean capacitiveValue()
{
  long total1 =  cs_12_13.capacitiveSensor(100);
  arrays[nextIndex] =  total1;
  //The "%" is the modulo operator. "a = b%c" gives you the remainder of dividing b by c
  nextIndex = (nextIndex + 1) % samples;
  m = nextIndex;
  for (int i = 0; i < samples; i++)
  {
    average = average + arrays[i];
  }
  average = average / samples;
#if defined debug
  Serial.print("Capacitance Value = ");                    // tab character for debug window spacing
  Serial.println(average);                  // print sensor output 1
#endif
  if (average > capacitiveThreshold) {
    return 1;
  }
  else {
    return 0;
  }
}

