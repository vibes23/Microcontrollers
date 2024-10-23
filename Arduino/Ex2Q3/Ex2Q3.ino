void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
Serial.begin(9600);
Serial.println("Setup done!");
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(A0) == LOW){
  Serial.println("Detected");
}
else{
    Serial.println("Where are you now??");
}
delay(20);
}
