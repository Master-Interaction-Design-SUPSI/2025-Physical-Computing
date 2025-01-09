int intensity = 0;
int direction = 1;  // 1: up, -1: down
int max_intensity = 50;

void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  
  if(intensity == 0) {
    direction = 1;  // up
  }
  if(intensity == max_intensity) {
    direction = -1;   // down
  }

  intensity += direction;   // intensity = intensity + direction

  analogWrite(10, intensity);

  delay(10);
}
