#include <rgb_lcd.h>
rgb_lcd lcd;

int pin_led = 12;
int pin_pot = A0;
int pot_value = 0;

bool led_status = 0;  // 0: LED off, 1: LED on
long old_millis_led1 = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(0, 255, 0);
  pinMode(pin_led, OUTPUT);
}

void loop() {
  lcd.clear();
  pot_value = analogRead(pin_pot);

  lcd.setCursor(0, 0);
  lcd.print(pot_value);

  lcd.setCursor(0, 1);
  lcd.print(millis());

  if(millis() - old_millis_led1 > 1000) { // non blocking "delay"
    if(led_status == 0) {
      digitalWrite(pin_led, HIGH);
      led_status = 1;
    }
    else {
      digitalWrite(pin_led, LOW);
      led_status = 0;
    }
    old_millis_led1 = millis();
  }

  delay(20);
}
