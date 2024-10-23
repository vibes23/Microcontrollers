void setup() {
  // put your setup code here, to run once:
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  digitalWrite(7,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println("Magnet ON");
  delay(2000);
  // digitalWrite(7,LOW);
  // Serial.println("Magnet OFF");
  // delay(2000);
}
