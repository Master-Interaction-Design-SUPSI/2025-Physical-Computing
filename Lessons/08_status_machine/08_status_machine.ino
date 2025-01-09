int pin_sel_btn = 11;   // selector button
bool old_sel_btn_status = 0;

int current_app = 1;  // 1: blink, 2: count, 3: sensor
int app_count = 3;

void setup() {
  Serial.begin(9600);
  pinMode(pin_sel_btn, INPUT);
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
  Serial.println("Current app is: " + String(current_app));
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
