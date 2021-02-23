#include "DHTesp.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif

#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to
#define DSB18B20DataPin 4  //D2

#define DHTDataPin 5      //D1


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(DSB18B20DataPin);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

DHTesp dht;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  String thisBoard = ARDUINO_BOARD;
  Serial.println(thisBoard);

  // Autodetect is not working reliable, don't use the following line
  // dht.setup(17);
  // use this instead:
  dht.setup(DHTDataPin, DHTesp::DHT22); // Connect DHT sensor to GPIO 2
  // Start the DS18B20 sensor
  sensors.begin();
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  Serial.print(dht.getStatusString());
  Serial.print("  Humidity :");
  Serial.print(humidity, 1);
  Serial.print("%\t\t Air Temperature :");
  Serial.print(temperature, 1);
  Serial.print("ºC");
  Serial.print("%\t\t Ground Temperature :");
  Serial.print(temperatureC);
  Serial.println("ºC");
  delay(2000);
}
