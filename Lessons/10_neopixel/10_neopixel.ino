#include <Adafruit_NeoPixel.h>

int pixels_count = 24;
byte pixels_pin = 6;

Adafruit_NeoPixel pixels(pixels_count, pixels_pin, NEO_GRB + NEO_KHZ800);

byte pin_x = A1;
byte pin_y = A0;

int x_value = 0;
int y_value = 0;

void setup() {
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  x_value = analogRead(pin_x);  // pixel amount
  y_value = analogRead(pin_y);  // color change

  Serial.println("x: " + String(x_value) + ", y: " + String(y_value));

  int x_value_mapped = map(x_value, 950, 3020, 0, pixels_count-1);
  int y_value_mapped = map(y_value, 960, 3020, 0, 255);

  pixels.clear();

  for(int i=0; i <= x_value_mapped; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, y_value_mapped));
  }

  pixels.show();

}

