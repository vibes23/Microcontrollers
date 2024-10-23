#include <Servo.h>

Servo myservo;  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(5);
  pinMode(A0,INPUT);
  Serial.println("Setup Done");
}

int pos = 1;
int step = 1;
void loop() {
  // put your main code here, to run repeatedly:
while(true){
  if(pos == 180||pos == 0){
    step *= -1;
  }

  
  Serial.println(pos);
  if(digitalRead(A0)==LOW){
    Serial.println("Dectected");
    continue;}
  else{
    pos += step;
  }

  myservo.write(pos);
  delay(50);
  }
}

