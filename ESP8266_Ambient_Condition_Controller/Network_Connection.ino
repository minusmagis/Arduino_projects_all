// This Script will take care of the connection to the network and to the MQTT server
#include "Definitions.h"

// We first need to set the wifi network credentials as well as the MQTT server Address
const char* ssid = "Can Maxwell";
const char* password = "Psk2Clmi342FaM8";
const char* mqtt_server = "192.168.1.159";

// We then initialize both the wifi and the MQTT Server connection
WiFiClient espClient;
PubSubClient client(espClient);

// We define the message variables as well as their buffer size
char Message[MSG_BUFFER_SIZE];

// We also define some char arrays that will hold the values of the different parameters
char Air_Humidity_Message[10];
char Air_Temperature_Message[10];
char Ground_Temperature_Message[10];
char Ground_Moisture_Message[10];

char Watering_Plants_Message[20];
char Watering_Plants_Status[10];

char Heating_Message[20];
char Heating_Status[10];

// --------------------------------------------------------------- Wifi Connection -----------------------------------------------------------------------

// This loop connects to the Wifi Network
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  // We only print on the serial if we desire
#ifdef SerialMessages
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
#endif

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // If the status is still not connected we wait for half a second
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
#ifdef SerialMessages
    Serial.print(".");
#endif
  }

  // Why is this here?
  randomSeed(micros());

  // If the connection is succesful we print the WiFi characteristics on the serial if we desire to
#ifdef SerialMessages
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
#endif
}

// --------------------------------------------------------------- MQTT Messaging -----------------------------------------------------------------------

// Now we need to define what does the callback function do depending on the received message
void callback(char* topic, byte* payload, unsigned int length) {
#ifdef SerialMessages
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
#endif
  const char* payload2 = reinterpret_cast<const char*>(payload);

  // We create a case switch to handle the different actions that can come from the publisher
  // If the incoming message is water we know we have to water the plants
  if (payload2[0] == 'W') {
    snprintf (Watering_Plants_Message, 20, "Watering Plants");
    client.publish("Watering_Plants", Watering_Plants_Message);
    Water_Plants();
    snprintf (Watering_Plants_Message, 20, "Plants Watered");
    client.publish("Watering_Plants", Watering_Plants_Message);
    // We call the water plants function
  }

  else if (payload2[0] == 'H') {
    int GroundHeatingValue = payload2[1];
    GroundHeatingValue -= 48;
    snprintf (Heating_Message, 20, "Heating %d", GroundHeatingValue);
    client.publish("Heating", Heating_Message);
    if (payload2[1] == '1') {
      GroundHeating(1);
    }
    else {
      GroundHeating(0);
    }
  }

  else {
#ifdef SerialMessages
    Serial.print("I did not understand the message");                 // In case the message is not understood we print a message on the serial print for debugging
#endif
    client.publish("InstructionsSlave", "I did not understand the message");    // We publish a message saying that we did not understand the question
  }
}

// --------------------------------------------------------------- MQTT connection -----------------------------------------------------------------------

// This function will connect the ESP8266 to the MQTT server and notify us when it is propperly connected
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
#ifdef SerialMessages
    Serial.print("Attempting MQTT connection...");
#endif

    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
#ifdef SerialMessages
      Serial.println("connected");                                                // If we succesfully connect we print it on the serial
#endif
      client.publish("GroundSensorStatus", "Ground Sensor is Online");            // We also publish a message acknowledgeing that the ground sensor is now online
      client.subscribe("InstructionsMaster");                                     // And we subscribe to the Channel where the master will send the instructions
    }

    // If the connection has failed we print the reason why it has failed and retry after 5 seconds
    else {
#ifdef SerialMessages
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
#endif
      delay(5000);
    }
  }
}


void UpdateStatus(float Air_Humidity, float Air_Temperature, float Ground_Temperature, float Ground_Moisture) {

  // If, for some reason we get disconnected from the MQTT server we try to reconnect
  if (!client.connected()) {
    reconnect();
  }

  // We update the client that will execute the callback function from above
  client.loop();

  snprintf (Message, MSG_BUFFER_SIZE, "Humidity %d%%   Air Temperature %4.2fºC   Ground Temperature %4.2fºC   Ground Moisture %d%% ", Air_Humidity, Air_Temperature, Ground_Temperature, Ground_Moisture);
  snprintf (Air_Humidity_Message, 10, "%d", Air_Humidity);
  snprintf (Air_Temperature_Message, 10, "%4.2f", Air_Humidity);
  snprintf (Ground_Temperature_Message, 10, "%4.2f", Air_Humidity);
  snprintf (Ground_Moisture_Message, 10, "%d", Air_Humidity);

#ifdef Debugging
  Serial.print("Publish message: ");
  Serial.println(Message);
#endif
  client.publish("GroundSensorStatus", Message);
  client.publish("Air_Humidity", Air_Humidity_Message);
  client.publish("Air_Temperature", Air_Temperature_Message);
  client.publish("Ground_Temperature", Ground_Temperature_Message);
  client.publish("Ground_Moisture", Ground_Moisture_Message);
}

void FastUpdate () {
  // We update the client that will execute the callback function from above
  client.loop();
}
