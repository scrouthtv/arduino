#define PULSEPIN 5

void setup() {
  pinMode(PULSEPIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long ontime = pulseIn(PULSEPIN, HIGH);
  unsigned long offtime = pulseIn(PULSEPIN, LOW);
  unsigned long period = ontime + offtime;
  double freq = 1000000.0 / period;
  Serial.print(ontime);
  Serial.print(" us + ");
  Serial.print(offtime);
  Serial.println(" us");
  Serial.print(freq);
  Serial.println(" Hz");
  // should be 337 kHz -> 3 us
  delay(1000);
}
