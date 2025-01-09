
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
  for(int i=0; i < app_count; i++) {
    if(msg.equals(appNames[i])) {
      current_app = i + 1;
      initApp();
    }
  }
}




