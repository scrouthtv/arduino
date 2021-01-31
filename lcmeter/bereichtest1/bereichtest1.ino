#define C1PIN 9

void setup() {
  Serial.begin(9600);
  pinMode(C1PIN, OUTPUT);
}

void loop() {
  Serial.println("passthru");
  digitalWrite(C1PIN, HIGH);
  delay(10000);
  Serial.println("closed");
  digitalWrite(C1PIN, LOW);
  delay(10000);
}
