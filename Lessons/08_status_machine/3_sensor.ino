void app3() {
  pot_value = analogRead(pin_pot);
  Serial.println(pot_value);

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(pot_value);

  delay(20);

}