#define BT1  2 // Green button on PD2
#define BT2  7 // Red button on PD7

#define LT1  3 // Light 1 on PWM on PD3
#define LT2 11 // Light 2 on PWM on PB3
#define LT3 10 // Light 3 on PWM on PB2

unsigned char brightness = 50;

const unsigned long minute = ((long) 1000) * 60; // 1 min in ms
const unsigned long hour = minute * 60; // 1 hr in ms

const unsigned long fadeStart = 1 * hour;
const unsigned long fadePerMinute = 5;

void setup() {
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
}

void loop() {
  if (millis() < fadeStart) {
    delay(10);
    if (digitalRead(BT1) == HIGH && brightness < 255)
      brightness += 1;
    if (digitalRead(BT2) == HIGH && brightness > 0)
      brightness -= 1;
  } else {
    delay(minute);
    brightness = max(brightness - fadePerMinute, 0);
  }

  analogWrite(LT1, brightness);
  analogWrite(LT2, brightness);
  analogWrite(LT3, brightness);
}
