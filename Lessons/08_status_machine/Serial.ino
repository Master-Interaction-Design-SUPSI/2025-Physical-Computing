
void readSerial() {

  if(Serial.available() > 0) {  // something is in the buffer
    String msg = "";
    msg = Serial.readStringUntil('\n');
    msg.trim();
    
    Serial.println(msg);
  }

}