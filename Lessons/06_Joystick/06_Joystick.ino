#include <ESP32Servo.h>
#include <rgb_lcd.h>

rgb_lcd lcd;
Servo servo;

int x_pin = A6;
int y_pin = A7;
int x_value = 0;
int y_value = 0;

int x_value_max = 3060;
int x_value_min = 950;
int y_value_max = 3060;
int y_value_min = 950;

void setup() {
  Serial.begin(9600);
  //lcd.begin(16, 2);
  servo.attach(9);  // pin
}
void loop() {
  
  x_value = analogRead(x_pin);
  y_value = analogRead(y_pin);

  Serial.println(x_value);

  int x_mapped = map(x_value, x_value_min, x_value_max, 0, 16);
  int y_mapped = map(y_value, y_value_min, y_value_max, 0, 16);
  int servo_value = map(x_value, x_value_min, x_value_max, 0, 180);

  servo.write(servo_value);

  lcd.clear();
  lcd.setCursor(x_mapped, 0);
  lcd.print('#');
  lcd.setCursor(y_mapped, 1);
  lcd.print('#');

  delay(50);
}















