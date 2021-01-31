#define CXPIN 11 // 47 nF
#define C0PIN 8 // 1 nF
#define C0VAL 10.0
#define CKVAL 0.720

#define CUNIT "nF"

volatile uint64_t count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(C0PIN, OUTPUT);
  pinMode(CXPIN, OUTPUT);

  cli();
  
  TCCR1A = 0;
  TCCR1B = (0 << ICES1) | (1 << CS12) | (1 << CS11) | (1 << CS10);
  TCCR1C = 0;

  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS22) | (0 << CS21) | (1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 256-1;

  sei();
}

void loop() {
  delay(1000);

  digitalWrite(C0PIN, LOW);
  digitalWrite(CXPIN, LOW);
  delay(10);
  const double f0 = count;
  
  digitalWrite(C0PIN, HIGH);
  digitalWrite(CXPIN, LOW);
  delay(10);
  const double f1 = count;

  digitalWrite(C0PIN, LOW);
  digitalWrite(CXPIN, HIGH);
  delay(10);
  const double f2 = count;

  Serial.print("f0 = ");
  Serial.print(f0);
  Serial.print("  f1 = ");
  Serial.print(f1);
  Serial.print("  f2 = ");
  Serial.println(f2);
  const double cr = (C0VAL - CKVAL + pow(f0 / f1, 2) * CKVAL) / (2 * pow(f0 / f1, 2) - 1);
  const double cx = (pow(f1 / f2, 2) - 1) * (CKVAL + cr) + pow(f1 / f2, 2) * C0VAL;
  Serial.print(cx);
  Serial.print(" ");
  Serial.println(CUNIT);
}

ISR(TIMER2_COMPA_vect) {
  count = TCNT1;
  TCNT1 = 0;
}
