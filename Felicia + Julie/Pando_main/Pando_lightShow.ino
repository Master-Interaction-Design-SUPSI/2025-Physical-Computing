
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