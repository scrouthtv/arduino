#define PWM1 9 // PB1
#define BUT 7 // PB0

#include "math.h"

unsigned char brightness = 50;
const unsigned long minute = 1000 * 60; // 1 minute in ms
const unsigned long hour = minute * 60; // 1 hour in ms

void setup() {
  pinMode(BUT, INPUT);
}

void loop() {
  brightness = min(255, brightness);
  brightness = max(0, brightness);
  analogWrite(PWM1, brightness); 
  
  if (millis() < hour) {
    if (digitalRead(INPUT) == HIGH) {
      brightness += 10;
    }
    delay(10);
  } else {
    brightnes = max(brightness - 5, 0);
    delay(minute);
  }
}
