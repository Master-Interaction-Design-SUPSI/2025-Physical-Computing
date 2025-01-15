// LIBRARIES
#include <Adafruit_Thermal.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif


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

int currentState = 0;
int randNumber;

// NeoPixel strips

// Julie's initial code
// int led_status = false;
// int pixels_count = 24;
// byte pixels_pin = 6;  // its actually pin nr. 3 on the arduino board
// Adafruit_NeoPixel pixels(pixels_count, pixels_pin, NEO_GRB + NEO_KHZ800);

// Declare NeoPixel strip objects
Adafruit_NeoPixel strip1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);

// Pin and LED count for the first NeoPixel strip
#define LED_PIN_1    6
#define LED_COUNT_1 24

// Pin and LED count for the second NeoPixel strip
#define LED_PIN_2    9
#define LED_COUNT_2 24



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

  // buttons
  bool btn_left = readButton(btn_left_pin, btn_left_val, old_btn_left_val, btn_left_status, old_btn_left_status);
  bool btn_right = readButton(btn_right_pin, btn_right_val, old_btn_right_val, btn_right_status, old_btn_right_status);

  // NeoPixel
  if (btn_left_status = 2 && btn_left_status = 2) {
    theaterChaseSync(strip1, strip2, strip1.Color(127, 127, 127), 50);
    rainbowSync(strip1, strip2, 10);
  }

  if (btn_left_status = 2) {
    lightGreen();
  }

  if (btn_right_status = 2) {
    lightRed();
  }

  // // Selecting message to print
  // getMessage(btn_left, btn_right, false);

  // // Printing the message
}


void eyeClose() {
  servo.write(0);
  delay(500);
}

void eyeOpen() {
  servo.write(90);
  delay(500);
}

void lightNeutral() {
  pixels.clear();

  for (int i = 0; i < LED_COUNT_1; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
  }
  pixels.show();
}

void lightRed() {
  pixels.clear();

  for (int i = 0; i < LED_COUNT_2; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
  }
  pixels.show();
}

void lightGreen() {
  pixels.clear();

  for (int i = 0; i < LED_COUNT_2; i++) {
    pixels.setPixelColor(i, pixels.ColorHSV(0, 255, 0));
  }
  pixels.show();
}



void loop() {

  void stateMachine() {
    switch (currentState) {
      case 0:  // init
        // if we detect motion go to 1
        break;
      case 1:  // ready
        // lightNeutral
        // eyeOpen
        // soundReady
        // we read the buttons
        bool btn_left = readButton(btn_left_pin, btn_left_val, old_btn_left_val, btn_left_status, old_btn_left_status);
        bool btn_right = readButton(btn_right_pin, btn_right_val, old_btn_right_val, btn_right_status, old_btn_right_status);

        if (btnLeft && btnRight) {
          currentState = 2;
        }
        if (btnLeft & != btnRight) {  // ??? will this work?
          currentState = 3;
        }
        if (btnRight) {
        }
        // after delay, go to case 5
      case 2:  // left
               // lightRed
               // soundLeft
               // counterLeft ++
               // print from String btnLeft[]
        andNumber = random(0, sizeof(btnLeft) / sizeof(btnLeft[0]));
        Serial.println(btnLeft[randNumber]);

        currentState = 1;  // goes back to ready, for presentation purposes
        break;
      case 3:  // right
               // lightGreen
               // soundRight
               // counterRight ++
               // print from String btnRight[]
        randNumber = random(0, sizeof(btnRight) / sizeof(btnRight[0]));
        Serial.println(btnRight[randNumber]);

        currentState = 1;  // goes back to ready, for presentation purposes
        break;
      case 4:  // both
               // lightShow
               // soundShow
               // print from String btnBoth[]

        randNumber = random(0, sizeof(btnBoth) / sizeof(btnBoth[0]));
        Serial.println(btnBoth[randNumber]);

        currentState = 5; // first part of the presentation is done, goes to stand-by

        break;
      case 5:  // stand-by
               // light off
               // eyeClose
               // after delay, go to case 6

        break;
      case 6: // printing motivational quote
              // eyeOpen
              // print from String quoteTime[]

        break;
    }
  }

  // Selecting message to print
  getMessage(btn_left, btn_right, false);
}
