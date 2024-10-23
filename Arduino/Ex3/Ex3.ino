const int green = 11;
const int blue = 10;
const int red = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  pinMode(A2, INPUT_PULLUP);

  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
  digitalWrite(blue,LOW);

  int red_base = 150;
  int blue_base = ;
  int green_base = 390;
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(red,HIGH);
  // digitalWrite(green,HIGH);
  digitalWrite(blue,HIGH);

  Serial.println(analogRead(A2));
  delay(100);
}
