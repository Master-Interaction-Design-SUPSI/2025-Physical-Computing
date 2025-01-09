int pin_buzzer = 10;

void setup() {
	Serial.println(9600);
	pinMode(pin_buzzer, OUTPUT);
}
void loop() {
	Serial.println("C4, 261Hz");
	tone(pin_buzzer, 261);
	delay(1000);
	
	Serial.println("D4, 293Hz");
	tone(pin_buzzer, 293);
	delay(1000);
	
	Serial.println("E4, 330Hz");
	tone(pin_buzzer, 330);
	delay(1000);
	
	Serial.println("F4, 349Hz");
	tone(pin_buzzer, 349);
	delay(1000);
	
	Serial.println("G4, 392Hz");
	tone(pin_buzzer, 392);
	delay(1000);
	
	Serial.println("A4, 440Hz");
	tone(pin_buzzer, 440);
	delay(1000);
	
	Serial.println("B4, 494Hz");
	tone(pin_buzzer, 494);
	delay(1000);

  Serial.println("C5, 523Hz");
	tone(pin_buzzer, 523);
	delay(1000);
}