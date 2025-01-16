#include "Adafruit_Thermal.h"

// #include "adalogo.h"
// #include "adaqrcode.h"

String btnLeft[] = { "YAY! You did it! You\’re basically unstoppable.", "High-five through the airwaves! Pando is so proud of you!", "Woohoo! Green lights all the way, legend. Let\’s keep this streak going!", "You\’re on fire (in a good way)! Keep smashing those goals!" };
String btnRight[] = { "A", "HB", "C", "G" };

String quoteTime[] = { "1", "2", "3", "4" };
String btnBoth[] = { "Red", "Blue", "Green" };

String getMessage(bool btn_left, bool btn_right, bool btn_time) {
  if (btnLeft && btnRight) {
    randNumber = random(0, sizeof(btnBoth) / sizeof(btnBoth[0]));
    Serial.println(btnBoth[randNumber]);
    return btnBoth[randNumber];
  }
  if (btnLeft) {
    randNumber = random(0, sizeof(btnLeft) / sizeof(btnLeft[0]));
    Serial.println(btnLeft[randNumber]);
    return btnLeft[randNumber];
  }
  if (btnRight) {
    randNumber = random(0, sizeof(btnRight) / sizeof(btnRight[0]));
    Serial.println(btnRight[randNumber]);
    return btnRight[randNumber];
  }
  if (quoteTime) {
    randNumber = random(0, sizeof(quoteTime) / sizeof(quoteTime[0]));
    Serial.println(quoteTime[randNumber]);
    return quoteTime[randNumber];
  }
}



// yay you're great
// Y:20       N: 10

// Adafruit_Thermal printer(&Serial0);
// void printMessage(bool btn_left, bool btn_right, bool btn_time) {
// }