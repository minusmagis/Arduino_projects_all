void StartCode() {
  //If we have defined serial messages we output a welcome message via serial
#ifdef SerialMessages
  Serial.begin(115200);
  Serial.println("ESP8266 Ambient Condition Controller");
  Serial.println("start");
  Serial.println("echo: ESP8266 Ambient Condition Controller 0.0.1");
  Serial.println("echo: Last Updated: 2021-01-09 | Author: minusmagis");
#endif

  // DHT Autodetect is not working reliably we will use this instead:
  Ambient_Sensor.setup(DHTDataPin, DHTesp::DHT22); // Connect DHT sensor to GPIO 5

  // Start the DS18B20 sensor
  Ground_Temp_Sensor.begin();

  // We define the wifi connection as well as the MQTT server direction and callback subroutines
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // We also define the Peristaltic Pump motor with the SpeedyStepper library methods
  PeristalticPump.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);

  // Finally we define the pins that will be outputs and inputs
  pinMode(MoistureReadPin, INPUT);
  pinMode(MoistureExcitePin, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  
  // If, for some reason we get disconnected from the MQTT server we try to reconnect
  if (!client.connected()) {
    reconnect();
  }
}
