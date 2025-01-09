// libraries
#include <rgb_lcd.h>
rgb_lcd lcd;

// pinout
byte pin_sel_btn = 11;   // selector button
byte pin_led = 12;
byte pin_pot = A0;

// apps
String appNames[] = {"blink", "count", "sensor"};

// variables
bool old_sel_btn_status = 0;
byte current_app = 1;  // 1: blink, 2: count, 3: sensor
byte app_count = 3;
bool led_status = 0;  // 0: OFF, 1: ON
int pot_value = 0;  // 0 ... 4095
unsigned long old_millis_led = 0;


void setup() {
  Serial.begin(9600);

  // pinout
  pinMode(pin_sel_btn, INPUT);
  pinMode(pin_led, OUTPUT);

  // init
  lcd.begin(16, 2);
  lcd.setRGB(255, 255, 0);
  lcd.print("App store");

  delay(1000);

}

void loop() {
  readSelBtn();
  runApp();
}

void runApp() {
  switch(current_app) {
    case 1:
      app1();
      break;
    case 2:
      app2();
      break;
    case 3:
      app3();
      break;
  }
}

void changeApp() {
  if(current_app == app_count) {
    current_app = 1;
  }
  else {
    current_app++;
  }
  Serial.println("Current app is: " + appNames[current_app - 1]);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setRGB(255, 255, 0);
  lcd.print(appNames[current_app - 1]);
  
  delay(100);
}

void readSelBtn() {
  bool btn_val = digitalRead(pin_sel_btn);

  if(btn_val == 1 && old_sel_btn_status == 0) { // rising edge
    changeApp();
    old_sel_btn_status = 1;
  }
  else if(btn_val == 0 && old_sel_btn_status == 1) { // falling edge
    old_sel_btn_status = 0;
  }
}
