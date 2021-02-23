// We need to include the header file so that we have all the definitions
#include "Definitions.h"

// Setup a oneWire instance to communicate with the DSB18B20 ground temperature sensor
OneWire oneWire(DSB18B20DataPin);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature Ground_Temp_Sensor(&oneWire);

//Initialize the DHT ambient sensor
DHTesp Ambient_Sensor;

void Get_Conditions () {

  // We add a delay so that the sensor has time to sample
  delay(Ambient_Sensor.getMinimumSamplingPeriod());

  // Then we store the values onto floats for further use
  float Air_Humidity = Ambient_Sensor.getHumidity();
  float Air_Temperature = Ambient_Sensor.getTemperature();

  // We also get the readings for the ground temperature
  Ground_Temp_Sensor.requestTemperatures();
  float Ground_Temperature = Ground_Temp_Sensor.getTempCByIndex(0);

  // Finally we measure the moisture level of the soil by using our custom built function
  float Ground_Moisture = GetMoisture();

#ifdef SerialMessages
  Serial.print(Ambient_Sensor.getStatusString());
  Serial.print("  Humidity :");
  Serial.print(Air_Humidity, 1);
  Serial.print("%\t\t Air Temperature :");
  Serial.print(Air_Temperature, 1);
  Serial.print("ºC");
  Serial.print("\t\t Ground Temperature :");
  Serial.print(Ground_Temperature);
  Serial.print("ºC");
  Serial.print("\t\t Ground Moisture :");
  Serial.print(Ground_Moisture);
  Serial.println("%");
#endif
  UpdateStatus(Air_Humidity,Air_Temperature,Ground_Temperature,Ground_Moisture);

}

// This function is used to generate a small delay to slow down the exciting frequency of the capacitive sensor
// Basically it takes some time to generate a random number so perform that action a number of times to delay the
// workings of any loop more precisely than the delayMicroseconds() function.
void ArtificialDelay(long Delay_Cycles)
{
  for (long i = 0; i < Delay_Cycles; i++) {
    int a = random(1);
  }
}

// With this function we determine the moisture level of the ground by exciting with a square wave and measuring the resulting
// impedance change between the sensor prongs when wet or dry. Then we map those values to a percentage and output the result as
// a float value.
float GetMoisture() {

  // This for loop generates a super fast square wave using direct port writing (around 500khz)
  for (long i = 0; i < 10000; i++) {
    GPOS = (1 << MoistureExcitePin);
    ArtificialDelay(CapacitiveDelay);
    GPOC = (1 << MoistureExcitePin);
    ArtificialDelay(CapacitiveDelay);
  }

  // After the excitation we read the voltage value on the analog pin and we store it on a variable
  long AnalogRead = analogRead(MoistureReadPin);
  delayMicroseconds(100);

  // In case we want to know the exact value of the sensor for debugging purposes we print it on the serial coms window.
  #ifdef Debugging
  Serial.print("Moisture sensor : ");
  Serial.println(AnalogRead);
  #endif

  // Finally we map directly the sensor values to a percent value. The scale is inverted due to the working mechanics of the sensor.
  float Moisture = map(AnalogRead, MinHumiditySensorValue, MaxHumiditySensorValue, 100, 0);
  return Moisture;
}
