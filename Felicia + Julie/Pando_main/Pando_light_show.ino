#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Pin and LED count for the first NeoPixel strip
#define LED_PIN_1 6 // its actually pin nr. 3
#define LED_COUNT_1 24

// Pin and LED count for the second NeoPixel strip
#define LED_PIN_2 9 // its actually pin nr. 6
#define LED_COUNT_2 24

// Declare NeoPixel strip objects
Adafruit_NeoPixel strip1(LED_COUNT_1, LED_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT_2, LED_PIN_2, NEO_GRB + NEO_KHZ800);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  // Initialize NeoPixel strips
  strip1.begin();
  strip1.show();   
  strip1.setBrightness(50); 
  
  strip2.begin();
  strip2.show(); 
  strip2.setBrightness(50); 
}

void loop() {
  // Apply synchronized effects to both strips
  theaterChaseSync(strip1, strip2, strip1.Color(127, 127, 127), 50);
  rainbowSync(strip1, strip2, 10);
}

// Update functions to work with both strips in sync
void colorWipeSync(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, uint32_t color, int wait) {
  for (int i = 0; i < strip1.numPixels(); i++) {
    strip1.setPixelColor(i, color);
    strip2.setPixelColor(i, color);
    strip1.show();
    strip2.show();
    delay(wait);
  }
}

void theaterChaseSync(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) {
    for (int b = 0; b < 3; b++) {
      strip1.clear();
      strip2.clear();
      for (int c = b; c < strip1.numPixels(); c += 3) {
        strip1.setPixelColor(c, color);
        strip2.setPixelColor(c, color);
      }
      strip1.show();
      strip2.show();
      delay(wait);
    }
  }
}

void rainbowSync(Adafruit_NeoPixel &strip1, Adafruit_NeoPixel &strip2, int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
    strip1.rainbow(firstPixelHue);
    strip2.rainbow(firstPixelHue);
    strip1.show();
    strip2.show();
    delay(wait);
  }
}
