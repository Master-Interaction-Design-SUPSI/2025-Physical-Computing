#include <Adafruit_Thermal.h>

//library

//Variable
//button 
bool btn_left_val = false;
bool old_btn_left_val = false;
int btn_left_pin = 11;
int btn_left_status = 0;  // 0: OFF, 1: RISING EDGE, 2: ON; 3: FALLING EDGE
int old_btn_left_status = -1;
int count_left = 0;

bool btn_right_val = false;
bool old_btn_right_val = false;
int btn_right_pin = 12;
int btn_right_status = 0;  
int old_btn_right_status = -1;
int count_right = 0;

int randNumber;

//LED 
#include <Adafruit_NeoPixel.h>
int led_status = false; 
int pixels_count = 24;
byte pixels_pin = 6; // its actually pin nr. 3 on the arudino board
Adafruit_NeoPixel pixels(pixels_count, pixels_pin, NEO_GRB + NEO_KHZ800);


void setup() {
	Serial.begin(9600);

  ///distance sensor
  //while (! Serial) {
  //  delay(1);
  //}
//
  //Serial.println("Adafruit VL53L0X test.");
  //if (!lox.begin(0x30)) {
  //  Serial.println(F("Failed to boot VL53L0X"));
  //  while(1);
  //}
  //// start continuous ranging
  //lox.startRangeContinuous();

  randomSeed(analogRead(0));

  //set up button
  pinMode(btn_left_pin, INPUT);
  pinMode(btn_right_pin, INPUT);

}

void loop() {

  //ultra sonic distance sensor
  //if (lox.isRangeComplete()) {
  //  Serial.print("Distance in mm: ");
  //  Serial.println(lox.readRange());
  //}

  //if (ultrasonic_distance >= 15 && ultrasonic_distance <= 20 && led_status == false){
  //  Serial.println("I am activated");
  //  lightNeutral();  //TODO: i need to make it light up gently 
  //  led_status = true; 
  //}
  
  bool btn_left = readButton(btn_left_pin, btn_left_val, old_btn_left_val, btn_left_status, old_btn_left_status);
  bool btn_right = readButton(btn_right_pin, btn_right_val, old_btn_right_val, btn_right_status, old_btn_right_status);


  if (btn_left_status = 2 && btn_left_status = 2){
    lightShow();

  }

  if (btn_left_status = 2 ){
    lightGreen();

  }

  if (btn_right_status = 2){
    lightRed();

  }

  // Selecting message to print
  getMessage(btn_left, btn_right, false);

  // Printing the message
}


void eyeClose(){
  servo.write(0);
  delay(500);
}

void eyeOpen(){
  servo.write(90);
  delay(500);
}

void lightNeutral(){
  pixels.clear();

   for(int i=0; i<pixels_count; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
  }
  pixels.show();
}

void lightRed(){
  pixels.clear();

   for(int i=0; i<pixels_count; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
  }
  pixels.show();
}

void lightGreen(){
  pixels.clear();

   for(int i=0; i<pixels_count; i++) {
      pixels.setPixelColor(i, pixels.ColorHSV(0, 255, 0));
  }
  pixels.show();
}

