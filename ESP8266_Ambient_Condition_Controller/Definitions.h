// GPIO where the DS18B20 ground temp sensor is connected to
#define DSB18B20DataPin 4  //D2

// GPIO where the DHT Ambient sensor is connected to
#define DHTDataPin 5      //D1

// We define the analogread pin and the Excitation pin for the capacitive sensor
#define MoistureReadPin A0 
#define MoistureExcitePin 14 //D5

// We define the relay pin for the ground heating element
#define HeaterPin 9 //S2

// We define the pins that control the peristaltic pump
#define MOTOR_STEP_PIN 12
#define MOTOR_DIRECTION_PIN 13
#define ENABLE_PIN 16

// We have to define the Peristaltic Pump motor speed and acceleration
#define PeristalticPump_Speed 10000
#define PeristalticPump_Acceleration 10000

// We also have to define the volume pumped in ml as well as the relation between the volume and the motor steps
#define PeristalticPump_Volume 50
#define VolumeToSteps 1000

// We also need to define the yield interval so that the ESP does not crash 
#define YeldInterval 100000

// We also define the delay for the Moisture Sensor excitation frequency (at a delay of 1 it excites at around 500khz
#define CapacitiveDelay 1

// We define the Status Update delay in miliseconds
#define StatusUpdateDelay 60000

// We also define the Message receive delay so that the ESP is not constantly probing the MQTT server
#define MessageReceiveDelay 1000

// We also need to define the values for the maximum and minimum value of the capacitive moisture sensor which will correspond to fully dry and fully soaked.
#define MaxHumiditySensorValue 700
#define MinHumiditySensorValue 500

// We define the maximum message size 
#define MSG_BUFFER_SIZE  (100)

// We define if we desire to debug or to enable the serial messages
//#define Debugging 1
#define SerialMessages 1
