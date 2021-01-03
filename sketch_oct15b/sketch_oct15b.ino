unsigned char a = 0, b = 255;

void setup() {
  Serial.begin(9600);
  a--;
  b++;
  Serial.println(a);
  Serial.println(b);
}

void loop() {
  
}
