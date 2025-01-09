
void readSerial() {
  if(Serial.available() > 0) {  // something is in the buffer
    String msg = "";
    msg = Serial.readStringUntil('\n');
    msg.trim();
    Serial.println("User message: " + msg);
    decodeSerial(msg);
  }
}

void decodeSerial(String msg) {
  bool match_found = false;
  String app_name;

  msg.toLowerCase();

  for(int i=0; i < app_count; i++) {
    app_name = appNames[i];
    app_name.toLowerCase();
    if(msg.equals(app_name)) {
      match_found = true;
      current_app = i + 1;
      break;
    }
  }

  if(match_found) {
    initApp();
  }
  else {
    Serial.println("Sorry, app not found!");
  }
}




