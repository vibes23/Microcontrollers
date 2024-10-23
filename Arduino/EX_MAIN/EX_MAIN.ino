#include <Servo.h>
#include <LiquidCrystal.h>

#define RED 9
#define GREEN 11
#define BLUE 10

Servo M1,M2;


uint8_t whitepart1 = 0;
uint8_t whitepart2 = 155;

int led_red = 0;
int led_green = 0;
int led_blue = 0;

int delay_time = 30;

const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int red_int = 255;
int green_int = 255;
int blue_int = 255;

void ManualCalibrate(){
  M1.write(0);

  digitalWrite(RED,HIGH);
  delay(delay_time);
  led_red = analogRead(A2);
  Serial.print("RED intensity :");
  Serial.println(led_red);
  delay(delay_time);
  digitalWrite(RED,LOW);
  
  digitalWrite(BLUE,HIGH);
  delay(delay_time);
  led_blue = analogRead(A2);
  Serial.print("BLUE intensity :");
  Serial.println(led_blue); 
  delay(delay_time);
  digitalWrite(BLUE,LOW);
  
  digitalWrite(GREEN,HIGH);
  delay(delay_time);
  led_green = analogRead(A2);
  Serial.print("GREEN intensity :");
  Serial.println(led_green);
  lcd.clear();
  delay(delay_time);
  digitalWrite(GREEN,LOW);
  
  char disp[30];
  sprintf(disp, "R:%dG:%dB:%d", led_red, led_green, led_blue);
  lcd.print(disp);
  Serial.println("\n");

}

void AutoCalibrate(){
  
  red_int = 255;
  green_int = 255;
  blue_int = 255;
  
  M1.write(0);

  analogWrite(RED,red_int);
  delay(delay_time);
  led_red = analogRead(A2);
  Serial.print("RED intensity :");
  Serial.println(led_red);
  delay(delay_time);
  digitalWrite(RED,LOW);

  analogWrite(BLUE,blue_int);
  delay(delay_time);
  led_blue = analogRead(A2);
  Serial.print("BLUE intensity :");
  Serial.println(led_blue); 
  delay(delay_time);
  digitalWrite(BLUE,LOW);
  
  analogWrite(GREEN,green_int);
  delay(delay_time);
  led_green = analogRead(A2);
  Serial.print("GREEN intensity :");
  Serial.println(led_green);
  lcd.clear();
  delay(delay_time);
  digitalWrite(GREEN,LOW);
  
  int max=0;

  if(led_red>led_blue){
    if(led_red>led_green){
      max = led_red;
    }else{
      max = led_green;
    }
  }else{
    if(blue_int>green_int){
      max = led_blue;
    }else{
      max = led_green;
    }
  }

  while(led_red<max){
    analogWrite(RED, --red_int);
    delay(delay_time);
    led_red = analogRead(A2);
    digitalWrite(RED,LOW);
    delay(delay_time);
  }

  while(led_green<max){
    analogWrite(GREEN, --green_int);
    delay(delay_time);
    led_green = analogRead(A2);
    digitalWrite(GREEN,LOW);
    delay(delay_time);
  }

  while(led_blue<max){
    analogWrite(BLUE, --blue_int);
    delay(delay_time);
    led_blue = analogRead(A2);
    digitalWrite(BLUE,LOW);
    delay(delay_time);
  }

  Serial.print("The red,green,blue pwm is");
  Serial.print(",");
  Serial.print(red_int);
  Serial.print(",");
  Serial.print(green_int);
  Serial.print(",");
  Serial.println(blue_int);

  Serial.print("The intensity red,green,blue");
  Serial.print(led_red);
  Serial.print(",");
  Serial.print(led_green);
  Serial.print(",");
  Serial.println(led_blue);
  Serial.println("\n");
}

void setup() {
  // put your setup code here, to run once:

  M1.attach(5);
  M2.attach(6);
  
  lcd.begin(16, 2);

  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);

  pinMode(A2,INPUT_PULLUP);

  Serial.begin(9600);

  Serial.println("Setup Done");  
}

void loop() {
  // put your main code here, to run repeatedly:
  // ManualCalibrate();
  AutoCalibrate();
  delay(5000);
}
