// LIBRARIES
#include <Adafruit_Thermal.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif
#include <ESP32Servo.h>
#include <Wire.h>

// VARIABLES

// button
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

// for the quote function
long quote_time = 0;
long last_quote_time = 0;

// // servo
Servo servo;

enum { INIT,
       READY,
       LEFT,
       RIGHT,
       BOTH,
       STANDBY,
       QUOTE,
       OFF } state = INIT;
int randNumber;
// NeoPixel strips

// Julie's initial code
// int led_status = false;
// int pixels_count = 24;
// byte pixels_pin = 6;  // its actually pin nr. 3 on the arduino board

// Pin and LED count for the first NeoPixel strip
#define LED_PIN_1 6
#define LED_COUNT_1 24

// Pin and LED count for the second NeoPixel strip
#define LED_PIN_2 9
#define LED_COUNT_2 24

// Declare NeoPixel strip objects
Adafruit_NeoPixel strip1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(9600);

  randomSeed(analogRead(0));

  // set up button
  pinMode(btn_left_pin, INPUT);
  pinMode(btn_right_pin, INPUT);

  // NeoPixel
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  strip1.begin();
  strip1.show();
  strip1.setBrightness(50);

  strip2.begin();
  strip2.show();
  strip2.setBrightness(50);
}

// void loop() {

//   //ultra sonic distance sensor
//   //if (lox.isRangeComplete()) {
//   //  Serial.print("Distance in mm: ");
//   //  Serial.println(lox.readRange());
//   //}

//   //if (ultrasonic_distance >= 15 && ultrasonic_distance <= 20 && led_status == false){
//   //  Serial.println("I am activated");
//   //  lightNeutral();  //TODO: i need to make it light up gently
//   //  led_status = true;
//   //}

//   // buttons
//   bool btn_left = readButton(btn_left_pin, btn_left_val, old_btn_left_val, btn_left_status, old_btn_left_status);
//   bool btn_right = readButton(btn_right_pin, btn_right_val, old_btn_right_val, btn_right_status, old_btn_right_status);

// Selecting message to print
//   // getMessage(btn_left, btn_right, false);

//   // // Printing the message
// }


// void eyeClose() {
//   servo.write(0);
//   delay(500);
// }

// void eyeOpen() {
//   servo.write(90);
//   delay(500);
// }

void lightNeutral() {
  strip1.clear();
  strip2.clear();

  for (int i = 0; i < LED_COUNT_1; i++) {
    strip1.setPixelColor(i, strip1.Color(255, 255, 255));
    strip2.setPixelColor(i, strip2.Color(255, 255, 255));
  }
  strip1.show();
  strip2.show();
}

void lightRed() {
  strip1.clear();
  strip2.clear();

  for (int i = 0; i < LED_COUNT_2; i++) {
    strip1.setPixelColor(i, strip1.Color(255, 0, 0));
    strip2.setPixelColor(i, strip2.Color(255, 0, 0));
  }
  strip1.show();
  strip2.show();
}

void lightGreen() {
  strip1.clear();
  strip2.clear();

  for (int i = 0; i < LED_COUNT_2; i++) {
    strip1.setPixelColor(i, strip1.ColorHSV(0, 255, 0));
    strip2.setPixelColor(i, strip2.ColorHSV(0, 255, 0));
  }
  strip1.show();
  strip2.show();
}

void loop() {

  quote_time += millis();
  if (last_quote_time - quote_time >= 1000 * 10) {
    state = QUOTE;
  }
  bool btn_left = readButton(btn_left_pin, btn_left_val, old_btn_left_val, btn_left_status, old_btn_left_status);
  bool btn_right = readButton(btn_right_pin, btn_right_val, old_btn_right_val, btn_right_status, old_btn_right_status);

  switch (state) {
    case INIT:
      Serial.println("Waiting for motion sensor");
      delay(1000);
      // {
      // if we detect motion go to 1
      // motion sensor doesn't work
      state = READY;
      break;
    // }
    case READY:
      // Serial.println("READY");
      lightNeutral();  // {
      // eyeOpen
      // soundReady
      // we read the buttons

      if (btn_left && btn_right) {
        state = BOTH;
      } else if (btn_left) {  // ??? will this work?
        state = LEFT;
      } else if (btn_right) {
        state = RIGHT;
      }
      // }
      // after delay, go to case 5
      break;

    case LEFT:  // {
      lightRed();
      // soundLeft();
      count_left++;
      // print from String btnLeft[]
      // randNumber = random(0, sizeof(btnLeft) / sizeof(btnLeft[0]));
      // Serial.println(btnLeft[randNumber]);

      state = READY;  // goes back to ready, for presentation purposes
      break;

    // }
    case RIGHT:
      {
        lightGreen();
        // soundRight();
        count_right++;
        // print from String btnRight[]
        // randNumber = random(0, sizeof(btnRight) / sizeof(btnRight[0]));
        // Serial.println(btnRight[randNumber]);

        state = READY;  // goes back to ready, for presentation purposes
      }
      break;


    case BOTH:
      {
        lightShow();
        // soundShow
        // print from String btnBoth[]
        String message = getMessage(true, true, false);
        Serial.println(message);


        state = STANDBY;  // first part of the presentation is done, goes to stand-by
      }
      break;

    case STANDBY:  // {
      strip1.clear();
      strip2.clear();
      strip1.show();
      strip2.show();
      // eyeClose
      Serial.println("hi");
      delay(2000);
      state = QUOTE;

      break;
      // }

    case QUOTE:
      {
        // { // printing motivational quote
        // eyeOpen
        // print from String quoteTime[]
        last_quote_time = quote_time;
        quote_time = 0;
        String message = getMessage(false, false, true);
        Serial.println(message);
        state = OFF;
      }
      break;

    case OFF:
      strip1.clear();
      strip2.clear();
      strip1.show();
      strip2.show();
      // eyesclose
      break;
  }

  // Selecting message to print
  // getMessage(btn_left, btn_right, false);
}




// if (btn_left_status == 2) {
//   lightGreen();
// }

// if (btn_right_status == 2) {
//   lightRed();
// }
