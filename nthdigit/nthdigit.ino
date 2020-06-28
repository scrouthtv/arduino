#include <math.h>

int nthdigit(const int number, const int digit) {
  return ((int) trunc(number / ((int) pow(10, digit)))) % 10;
}

void setup() {
  const int number = 5678;
  const int digit = 2;
  Serial.begin(9600);

  Serial.println("-----------");
  Serial.println((number / 100) % 10); // 6
  Serial.println(((int) trunc(number / ((int) pow(10, digit)))) % 10); // 6
  Serial.println(nthdigit(number, 2)); // 7???????
  // this does   ((int) trunc(number / ((int) pow(10, digit)))) % 10;
}

void loop() {}
