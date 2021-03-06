#define BT1 13 // PB4
#define BT2 12 // PB4
#define POT 2 // PC2 analog2

void setup() {
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.print(analogRead(POT));
  Serial.print("  ");
  Serial.print(digitalRead(BT1));
  Serial.print("  ");
  Serial.println(digitalRead(BT2));
}
