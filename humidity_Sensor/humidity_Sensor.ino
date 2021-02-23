#include SPI.h

#include ESP8266WiFi.h

#include DHT.h

#define DHTPIN 2 // Digital pin 4

#define DHTTYPE AM2301 // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600); // See the connection status in Serial Monitor

  dht.begin();

}

void loop() {
  float h = dht.readHumidity();

  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {

    Serial.println("Failed to read from DHT sensor!");
  }

  else () {
    Serial.print("Humidity : ");
    Serial.print(h);
    Serial.print("    Temperature : ");
    Serial.print(t);
  }

}
