#include <Adafruit_NeoPixel.h>

int pixels_count = 24;
byte pixels_pin = 6;

Adafruit_NeoPixel pixels(pixels_count, pixels_pin, NEO_GRB + NEO_KHZ800);

byte pin_x = A1;
byte pin_y = A0;
byte pin_pot = A3;

int x_value = 0;
int y_value = 0;
int pot_value = 0;

int current_pixel = 0;  

void setup() {
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  x_value = analogRead(pin_x);  // V value, light intensity, 0..255
  y_value = analogRead(pin_y);  // H value, Hue (color), 0...65536
  pot_value = analogRead(pin_pot);  // S value, saturation, 0...255

  Serial.println("x: " + String(x_value) + ", y: " + String(y_value));

  int x_value_mapped = map(x_value, 950, 3020, 0, 255); // V value
  int y_value_mapped = map(y_value, 960, 3020, 0, 65536); // H value
  int pot_value_mapped = map(pot_value, 0, 4095, 0, 255); // S value

  pixels.clear();

  // pixels.setPixelColor(current_pixel, pixels.ColorHSV(y_value_mapped, pot_value_mapped, x_value_mapped));

  
  for(int i=0; i<pixels_count; i++) {
    if(i == current_pixel) {
      pixels.setPixelColor(i, pixels.ColorHSV(y_value_mapped, pot_value_mapped, x_value_mapped));
    }
    else {
      pixels.setPixelColor(i, pixels.ColorHSV(0, 0, 5));
    }
  }
  

  pixels.show();

  if(current_pixel == pixels_count - 1) {
    current_pixel = 0;
  }
  else {
    current_pixel++;
  }

  delay(100);

}

