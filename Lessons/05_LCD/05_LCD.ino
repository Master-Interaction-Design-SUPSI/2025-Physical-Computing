#include <Ultrasonic.h>
#include <rgb_lcd.h>

rgb_lcd lcd;
Ultrasonic ultrasonic_sensor(11);

long ultrasonic_distance = 0;
int pot_pin = A0;
int pot_value = 0;
int light_pin = A2;
int light_value = 0;
int buzzer_pin = 10;

int light_value_max = 4095;
int light_value_min = 1000;

void setup() {
  lcd.begin(16, 2);
  lcd.print("HI LCD!");
  lcd.setRGB(0, 255, 0);

  pinMode(buzzer_pin, OUTPUT);
}

void loop() {
  lcd.clear();

  pot_value = analogRead(pot_pin);
  ultrasonic_distance = ultrasonic_sensor.MeasureInCentimeters();

  light_value = analogRead(light_pin);

  // Potentiometer
  lcd.setCursor(0, 0);  // first character, first line
  lcd.print("P: " + String(pot_value));

  // Light sensor
  lcd.setCursor(8, 0);  // 8th character, first line
  lcd.print("L: " + String(light_value));

  // Distance sensor
  lcd.setCursor(0, 1);  // first character, second line

  if(ultrasonic_distance > 400) {
    lcd.print("U: Out of range");
  }
  else {
    lcd.print("U: " + String(ultrasonic_distance) + "cm");
  }

  mapValues();
  updateRGB();
  playBuzzer();

  delay(50);
  
}

void playBuzzer() {
  int buzzer_freq = pot_value + light_value + ultrasonic_distance;
  tone(buzzer_pin, buzzer_freq);
}

void mapValues() {

  // Potentiometer
  pot_value = map(pot_value, 0, 4095, 0, 255);

  // Light sensor
  light_value = map(light_value, light_value_max, light_value_min, 255, 0);

  // Distance sensor
  if(ultrasonic_distance <= 400) {
    ultrasonic_distance = map(ultrasonic_distance, 0, 400, 0, 255);
  }

}

void updateRGB() {
  lcd.setRGB(pot_value, light_value, ultrasonic_distance);  
}

