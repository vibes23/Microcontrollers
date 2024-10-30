#include <Servo.h>
#include <LiquidCrystal.h>

#define RED 9
#define GREEN 11
#define BLUE 10
#define EM 6
#define LDR A2
#define PROX 12
#define AVG_LEN 3

Servo M1,M2;

int tol = 8;
bool out[AVG_LEN];

// Initializes the out array to all false values.
void init_out(){
  for(int i = 0; i < AVG_LEN; i++){
    out[i] = false;
  }
}

uint8_t whitepart1 = 0;
uint8_t whitepart2 = 155;

int led_red = 0;
int led_green = 0;
int led_blue = 0;

int delay_time = 50;

const int rs = 2, en = 3, d4 = 4, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int red_int = 255;
int green_int = 255;
int blue_int = 255;

/**
 * @brief Manually calibrates the intensities of the red, green, and blue LEDs.
 * 
 * This function sequentially activates each of the RGB LEDs and measures their
 * intensities using an respective potentiometer. The measured intensities are printed to the
 * serial monitor and displayed on an LCD. The function starts by setting the servo
 * motor position to 0 which is white, then each LED is turned on, its intensity is measured, and
 * the LED is turned off. The intensities are read from analog pin A2 and stored in
 * the variables led_red, led_green, and led_blue. The results are printed on the LCD
 * in the format "R:<red_intensity>G:<green_intensity>B:<blue_intensity>".
 */
void ManualCalibrate(){
  M1.write(0);

  digitalWrite(RED,HIGH);
  delay(delay_time);
  led_red = analogRead(LDR);
  Serial.print("RED intensity :");
  Serial.println(led_red);
  delay(delay_time);
  digitalWrite(RED,LOW);
  
  digitalWrite(BLUE,HIGH);
  delay(delay_time);
  led_blue = analogRead(LDR);
  Serial.print("BLUE intensity :");
  Serial.println(led_blue); 
  delay(delay_time);
  digitalWrite(BLUE,LOW);
  
  digitalWrite(GREEN,HIGH);
  delay(delay_time);
  led_green = analogRead(LDR);
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

/**
 * @brief Calibrates the red, green, and blue LEDs to their maximum intensities using a simple algorithm.
 * The algorithm works by setting the PWM values of the LEDs to their maximum values, and then decreasing
 * the value until the detected intensity is equal to the maximum intensity of the three LEDs.
 * 
 * The function first sets the PWM values of the LEDs to their maximum values, and then reads the intensities
 * of the LEDs and stores them in the variables led_red, led_green, and led_blue. It then finds the maximum
 * intensity of the three LEDs and stores it in the variable max. It then enters a while loop for each of the
 * LEDs, decreasing the PWM value until the detected intensity is equal to the maximum intensity. Finally, it
 * prints the PWM values and the intensities of the LEDs to the serial monitor.
 */
void AutoCalibrate(){
  
  red_int = 255;
  green_int = 255;
  blue_int = 255;
  
  M1.write(0);  

  analogWrite(RED,red_int);
  delay(delay_time);
  led_red = analogRead(LDR);
  Serial.print("RED intensity :");
  Serial.println(led_red);
  delay(delay_time);
  digitalWrite(RED,LOW);

  analogWrite(BLUE,blue_int);
  delay(delay_time);
  led_blue = analogRead(LDR);
  Serial.print("BLUE intensity :");
  Serial.println(led_blue); 
  delay(delay_time);
  digitalWrite(BLUE,LOW);
  
  analogWrite(GREEN,green_int);
  delay(delay_time);
  led_green = analogRead(LDR);
  Serial.print("GREEN intensity :");
  Serial.println(led_green);
  lcd.clear();
  delay(delay_time);
  digitalWrite(GREEN,LOW);
  
  int max = max(led_red, max(led_green, led_blue));

  while(led_red<max){
    analogWrite(RED, --red_int);
    delay(delay_time);
    led_red = analogRead(LDR);
    digitalWrite(RED,LOW);
    delay(delay_time);
  }

  while(led_green<max){
    analogWrite(GREEN, --green_int);
    delay(delay_time);
    led_green = analogRead(LDR);
    digitalWrite(GREEN,LOW);
    delay(delay_time);
  }

  while(led_blue<max){
    analogWrite(BLUE, --blue_int);
    delay(delay_time);
    led_blue = analogRead(LDR);
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

  Serial.println("Auto-Calibration Done\n");
}

void setup() {
  M1.attach(5);
  M2.attach(6);
  M1.write(0);
  M2.write(60);
  lcd.begin(16, 2);

  pinMode(RED,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(LDR,INPUT_PULLUP);

  init_out();
  Serial.begin(9600);

  Serial.println("Setup Done");  
}

/**
 * @brief Controls the electromagnet by energizing or de-energizing it.
 * @param energize: 1 to energize the electromagnet, 0 to de-energize it (default is 0).
 */
void EMctrl(int energize = 0){  //energize = 1 for energize, 0 for de-energize
  digitalWrite(EM,energize);
}

/**
 * @brief Identifies the color of the object currently in front of the sensor.
 * @param color: 0 for general color region identification, 1 to check if red, 2 to check if green, 3 to check if blue
 * @return true if the color matches the specified color, false otherwise
 */
bool location(int color = 0){
  int red_cur, blue_cur, green_cur;
   
  analogWrite(RED,red_int);
  delay(delay_time);
  red_cur = analogRead(LDR);
  delay(delay_time);
  digitalWrite(RED,LOW);

  analogWrite(GREEN,green_int);
  delay(delay_time);
  green_cur = analogRead(LDR);
  delay(delay_time);
  digitalWrite(GREEN,LOW);

  analogWrite(BLUE,blue_int);
  delay(delay_time);
  blue_cur = analogRead(LDR);
  delay(delay_time);
  digitalWrite(BLUE,LOW);
    
  if(color == 1){ // check whether the color is red
    if(isColor(red_cur, green_cur, blue_cur) == 1){
      // Serial.println("Red");
      return true;
    }
    return false;
  }else if(color == 2){ //check whether the color is green
    if(isColor(red_cur, green_cur, blue_cur) == 2){
      // Serial.println("Green");
      return true;
    }
    return false;
  }else if(color == 3){ //check whether the color is blue
    if(isColor(red_cur, green_cur, blue_cur) == 3){
      // Serial.println("Blue");
      return true;
    }
    return false;
  }else if (color == 0){  //check what is the color in general for debugging
    switch (isColor(red_cur, green_cur, blue_cur)) {
      case 0: Serial.println("White"); break;
      case 1: Serial.println("Red"); break;
      case 2: Serial.println("Green"); break;
      case 3: Serial.println("Blue"); break;
    }
    return false;
  }  
}

/**
 * @brief Compares the values of red_cur, green_cur, and blue_cur to determine which color is currently being detected.
 * 
 * @param red_cur The current value of the red LED from LDR.
 * @param green_cur The current value of the green LED from LDR.
 * @param blue_cur The current value of the blue LED from LDR.
 * 
 * @return A value representing the color that is currently being detected.
 * 0: White
 * 1: Red
 * 2: Green
 * 3: Blue
 */
int isColor(int red_cur, int green_cur, int blue_cur) {
  if((red_cur+tol)<(green_cur+blue_cur)/2){
    return 1;
  } else if((green_cur+tol)<(red_cur+blue_cur)/2){
    return 2;
  }  else if((blue_cur+tol)<(red_cur+green_cur)/2){
    return 3;
  }else{
    return 0;
  }
}

/**
 * @brief Reads input from the serial monitor and returns the input as an integer.
 * 
 * @return The integer value of the input received from the serial monitor.
 * -1: Invalid input
 */
int readSerialInput() {
  char receivedChar = Serial.read();
  if (receivedChar >= '0' && receivedChar <= '9') {
    return receivedChar - '0';
  }else{
    Serial.println("Invalid input.");
    return -1;
  }
}

int input = -1;
bool picked = false;
bool is_valid =  true; // to limit printing of invalid input

void loop(){
  if (Serial.available()) {
    input = readSerialInput();
  }
  if(input<0){
    Serial.println("Press 1 for manual calibration.");
    Serial.println("Press 2 for auto calibration.");
    Serial.println("Press 3 to  check colour regions.");
    Serial.println("Press 4 to pick up and drop.\n");
    input = 0;
  }
  if(input>0){
    Serial.println("Press 0 to stop\n");
  }
  if(input==1){
    ManualCalibrate();
  }
  if(input==2){
    AutoCalibrate();
    input = 0;
  }
  
  if(input==3){
    for (int pos = 0; pos <= 180; pos += 1){
      M1.write(pos);
      location();
    }
    for (int pos = 180; pos >= 0; pos -= 1){
      M1.write(pos);
      location();
    }
    input = 0;
  }

  if(input==4){
    int pick = -1;
    int drop = -1;

    Serial.println("Press 1 to pick up at red.");
    Serial.println("Press 2 to pick up at green.");
    Serial.println("Press 3 to pick up at blue.\n");
    
    is_valid = false;
    while(true){
      if(Serial.available()){
        pick = readSerialInput();
        is_valid = true;  //getting update when input is read
      }
      if(pick==1 || pick==2 || pick==3){
        break;
      }else{
        if(is_valid){ //to prevent constant printing of the same message
          Serial.println("Please select valid option.");  
          is_valid = false; //resetting flag to prevent printing again until input is received
        }
      }
    }

    Serial.println("Press 1 to drop at red.");
    Serial.println("Press 2 to drop at green.");
    Serial.println("Press 3 to drop at blue.");
    
    is_valid = false;
    while(true){
      if(Serial.available()){
        drop = readSerialInput();
        is_valid = true;  //getting update when input is read
      }
      if(drop==1 || drop==2 || drop==3){
        break;
      }else if(c!='\n'){
        if(is_valid){ //to prevent constant printing of the same message
          Serial.println("Please select valid option");
          is_valid = false; //resetting flag to prevent printing again until input is received
        }
      }
    }

    int pos = 0;  //init position
    int dir = 1;  //init direction

    while (true){     //code to pickup
      bool validate = true;
      M1.write(pos);

      // Shift elements in the array to the right
      for (int index = AVG_LEN - 2; index >= 0; index--) {
        out[index + 1] = out[index];
      }
      out[0] = location(pick); // Update the first element with the current location check

      // Validate the last AVG_LEN readings
      // If any of them is false, break the loop
      for (int i = 0; i < AVG_LEN; i++) {
        if (!out[i]) {
          validate = false; // If any of the readings is false, set validate to false
          break;
        }
      }

      if(validate){ 
        //activate motor and EM  
        M2.write(120);
        EMctrl(1);
        delay(1000);
        //retract motor
        M2.write(60);
        delay(1000); 
        picked = true;
        Serial.println("Picked the target");
        break;
      }

      pos = pos + dir; // Update the position
      if(pos>=180 || pos<=0){ //changing direction of motor if it goes out of range
        dir *= -1;
      }
    }

    while (true){
      bool validate = true;
      M1.write(pos);

      // Shift elements in the array to the right
      for (int index = AVG_LEN - 2; index >= 0; index--) {
        out[index + 1] = out[index];
      }
      out[0] = location(drop); // Update the first element with the current location check
      for (int i = 0;i<AVG_LEN;i++){

        if(out[i] == false){
        validate = false;
        }
      } 

      if(validate && picked){ 
      // && (digitalRead(PROX)==HIGH)){
        M2.write(120);
        EMctrl(0);
        delay(1000);
        M2.write(60);
        // picked = false;
        Serial.println("Dropped the target");
        break;
      }

      pos = pos + dir; 
      if(pos>=180 || pos<=0){
        dir *= -1;
      }
    }
    M1.write(0);
  }
}  