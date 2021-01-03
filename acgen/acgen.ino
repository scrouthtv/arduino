#define POT 3 // analog 3
#define BT1 6
#define BT2 13
#define OUT 9

void setup() {
  pinMode(OUT, OUTPUT);
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);

  Serial.begin(9600);
  
  cli(); // disable timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 65535; // gen waveform every second tick
  TIMSK1 |= (1 << OCIE1A); // interrupt on Compare Match
  TCCR1B |= (1 << WGM12); // CTC up to OCR1A
  TCCR1B |= (1 << CS10); // no prescaler

  sei(); // enable timer
}

bool on = true;

ISR(TIMER1_COMPA_vect) {
  on = !on;
  digitalWrite(OUT, on);
  //Serial.println();
}

bool pressed1 = false, pressed2 = false;
uint8_t speed = 0;
// 0 no prescaler
// 1 clock / 8
// 2 clock / 64
// 3 clock / 256
// 4 clock / 1024
void setPrescaler() {
  switch (speed) {
    // on the atmega168 these are the lowest 3 bits on TCCR1B
    // so CS12 = 2, CS11 = 1, CS10 = 0
    // so this technically could be simplified by simply in- or de-
    // crementing the last 3 bits.
    // However, this would not be compatible for other chips.
    // In practice all the shift statements are optimized away
    // by the compiler anyways.
    case 0:
      TCCR1B = (0 << CS12) | (0 << CS11) | (1 << CS10);
      break;
    case 1:
      TCCR1B = (0 << CS12) | (1 << CS11) | (0 << CS10);
      break;
    case 2:
      TCCR1B = (0 << CS12) | (1 << CS11) | (1 << CS10);
      break;
    case 3:
      TCCR1B = (1 << CS12) | (0 << CS11) | (0 << CS10);
      break;
    case 4:
      TCCR1B = (1 << CS12) | (0 << CS11) | (1 << CS10);
      break;
  }
}

void loop() {
  //Serial.println(analogRead(POT));
  OCR1A = analogRead(POT);
  
  if (digitalRead(BT1) == HIGH) {
    if (!pressed1) {
      pressed1 = true;
      speed = speed == 4 ? 0 : speed + 1;
      setPrescaler();
    }
  } else if (pressed1) pressed1 = false;
  if (digitalRead(BT2) == HIGH) {
    if (!pressed2) {
      pressed2 = true;
      speed = speed == 0 ? 4 : speed - 1;
      setPrescaler();
    }
  } else if (pressed2) pressed2 = false;

  //Serial.println(speed);
  //Serial.println(TCCR1B);

  delay(100);
}
