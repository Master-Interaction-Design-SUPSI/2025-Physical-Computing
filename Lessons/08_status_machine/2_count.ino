unsigned int app2_count;

void app2() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(app2_count);

  app2_count++;

  delay(20);
}
