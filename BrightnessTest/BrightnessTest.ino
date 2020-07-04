#define LED 8 // led on PB0 (digital 8)
#define TMP 2 // LM335Z on PC2 (analog 2)

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
}

void loop() {
  Serial.println(temparature(analogRead(TMP)));
  delay(100);
}

double temparature(int analog) {
  double volts = 5.0 * analog / 1023.0;
  //Serial.println(volts);
  return 25 + ((volts - 2.98) / .01);
}
