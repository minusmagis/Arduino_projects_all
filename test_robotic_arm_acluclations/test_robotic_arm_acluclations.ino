void setup() {
  Serial.begin(9600);
  long y = 150;
  long r = 150;
  float pi =3.14159265;
  float result =(90-((atan((-y*sqrt(90000-sq(r)-sq(y))+r*sqrt(sq(r)+sq(y)))/(r*sqrt(90000-sq(r)-sq(y))+y*sqrt(sq(r)+sq(y)))))*180/pi));
  Serial.println(result);
}

void loop() {
  // put your main code here, to run repeatedly:

}
