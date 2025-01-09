void app1() {
  // init

  if(millis() - old_millis_led > 1000) { // non blocking "delay"
    if(led_status == 0) {
      digitalWrite(pin_led, HIGH);
      led_status = 1;
    }
    else {
      digitalWrite(pin_led, LOW);
      led_status = 0;
    }
    old_millis_led = millis();
  }

}