#define C1PIN 11

const double referenceValue = 720; // pF
double referenceTicks = 0;
volatile uint64_t count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(C1PIN, OUTPUT);

  cli();
  
  TCCR1A = 0;
  TCCR1B = (0 << ICES1) | (1 << CS12) | (1 << CS11) | (1 << CS10);
  TCCR1C = 0;

  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS22) | (0 << CS21) | (1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 256-1;

  sei();

  // reference value:
  digitalWrite(C1PIN, LOW);
  delay(10);
  referenceTicks = count;
}

void loop() {
  digitalWrite(C1PIN, HIGH);
  delay(1000);
  long mycount = count;
  double myC = referenceValue * (pow(referenceTicks, 2) / pow(mycount, 2) - 1);
  Serial.print("on: ");
  Serial.print(myC);
  Serial.print(" pF #");
  Serial.println(mycount);
  digitalWrite(C1PIN, LOW);
  delay(1000);
  mycount = count;
  myC = referenceValue * (pow(referenceTicks, 2) / pow(mycount, 2) - 1);
  Serial.print("off: ");
  Serial.print(myC);
  Serial.print(" pF #");
  Serial.println(mycount);
}

ISR(TIMER2_COMPA_vect) {
  count = TCNT1;
  TCNT1 = 0;
}
