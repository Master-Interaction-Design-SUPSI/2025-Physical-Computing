#include "Adafruit_VL53L0X.h"The_annoying_TOF_vl53l0x_continuous | Arduino IDE 2.3.3
123456789111213141516171819202122232425262728293010
  // start continuous ranging
  lox.startRangeContinuous();
}The_annoying_TOF_vl53l0x_continuous | Arduino IDE 2.3.3
1141516171819202123242526272829302223456789101112133132333435363738394041424344454647484950
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  lox.startRangeContinuous();
}

void loop() {
  if (lox.isRangeComplete()) {
    Serial.print("Distance in mm: ");
    Serial.println(lox.readRange());



void loop() {
  if (lox.isRangeComplete()) {
    Serial.print("Distance in mm: ");
    Serial.println(lox.readRange());
  }
}


Adafruit_VL53L0X lox = Adafruit_VL53L0X();

//#define XSHUT 11

void setup() {
  Serial.begin(115200);


    // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test.");

  //pinMode(XSHUT, OUTPUT);
  //digitalWrite(XSHUT, LOW);
  //delay(10);
  //digitalWrite(XSHUT, HIGH);
  //delay(10);

  if (!lox.begin(0x29)) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power
  Serial.println(F("VL53L0X API Continuous Ranging example\n\n"));

  // start continuous ranging
  lox.startRangeContinuous();
}

void loop() {
  if (lox.isRangeComplete()) {
    Serial.print("Distance in mm: ");
    Serial.println(lox.readRange());
  }
}