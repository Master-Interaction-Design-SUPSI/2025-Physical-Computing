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


void setup() {
	Serial.begin(9600);

  randomSeed(analogRead(0));

  //set up button
  pinMode(btn_left_pin, INPUT);
  pinMode(btn_right_pin, INPUT);

}

void loop() {
  
  bool btn_left = readButton(btn_left_pin, btn_left_val, old_btn_left_val, btn_left_status, old_btn_left_status);
  bool btn_right = readButton(btn_right_pin, btn_right_val, old_btn_right_val, btn_right_status, old_btn_right_status);

  // Selecting message to print
  getMessage(btn_left, btn_right, false);

  // Printing the message
}


