#define ReadPin A0
#define SquarewavePin 14
float a = 0;
#define Delay 1
#define Sensor1ActivatePin 13
#define Sensor2ActivatePin 12
long Sensor1 = 0;
long Sensor2 = 0;

void setup() {
  pinMode(SquarewavePin, OUTPUT);
  pinMode(Sensor1ActivatePin, OUTPUT);
  pinMode(Sensor2ActivatePin, OUTPUT);
  Serial.begin(2000000);
}

void ArtificialDelay(long Nanoseconds)
{
  for (long i = 0; i < Nanoseconds; i++) {
    int a = random(1);
  }
}

void loop() {
  GPOS = (1 << Sensor1ActivatePin);
  GPOC = (1 << Sensor2ActivatePin);

  for (long i = 0; i < 10000; i++) {
    GPOS = (1 << SquarewavePin);
    ArtificialDelay(Delay);
    GPOC = (1 << SquarewavePin);
    ArtificialDelay(Delay);
  }

  Sensor1 = analogRead(ReadPin);
  delayMicroseconds(100);

  GPOS = (1 << Sensor2ActivatePin);
  GPOC = (1 << Sensor1ActivatePin);
  for (long i = 0; i < 10000; i++) {
    GPOS = (1 << SquarewavePin);
    ArtificialDelay(Delay);
    GPOC = (1 << SquarewavePin);
    ArtificialDelay(Delay);
  }

  Sensor2 = analogRead(ReadPin);
  delayMicroseconds(100);



  Serial.print("Sensor 1 : ");
  Serial.print(Sensor1);
  Serial.print("    Sensor 2 : ");
  Serial.println(Sensor2);

  GPOC = (1 << Sensor2ActivatePin);
  GPOC = (1 << Sensor1ActivatePin);
}
