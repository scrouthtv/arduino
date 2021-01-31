#define LXPIN 5

void setup() {
  Serial.begin(9600);
  pinMode(LXPIN, INPUT);
}

unsigned long duration;

void loop() {
  duration = pulseIn(LXPIN, HIGH);
  Serial.println(duration);
  delay(1000);
}
