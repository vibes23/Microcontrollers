#include <Servo.h>

Servo myservo;  
int operation;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(5);
  Serial.println("Setup Done");
  operation = 0;
}

int pos = 1;
int step = 1;


void loop() {  
while(true){
  if(Serial.available()>0)
  {
    String s = Serial.readStringUntil('\n');
    Serial.println(s);
    operation = s.toInt();
  }
  if(pos == 180||pos == 0){
    step *= -1;
  }

  if(operation==0){
    Serial.println("Stop");
    }
  else{
    Serial.println("Move");
    pos += step;
  }

  myservo.write(pos);
  delay(100);
  }
}
