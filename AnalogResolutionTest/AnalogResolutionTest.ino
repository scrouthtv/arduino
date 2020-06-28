#define port 1

void setup() {
  Serial.begin(9600);

  for (int i = 8; i <= 32; i++) {
    Serial.println(analogRead(port));
  }
}

void loop() {
  
}
