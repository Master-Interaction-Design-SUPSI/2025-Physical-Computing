#include <Adafruit_NeoPixel.h>

int pixels_count = 24;
byte pixels_pin = 6;

Adafruit_NeoPixel pixels(pixels_count, pixels_pin, NEO_GRB + NEO_KHZ800);

void setup() {

  pixels.begin();
  delay(500);

}

void loop() {

}
