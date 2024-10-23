const int redPin = 11;
const int greenPin = 12;
const int bluePin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(bluePin,HIGH);
  digitalWrite(redPin,HIGH);
  digitalWrite(greenPin,HIGH);
}
