
const int tensPins[4]  = {2, 3, 4, 5};
const int unitsPins[4] = {6, 7, 8, 9};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(tensPins[i], OUTPUT);
    pinMode(unitsPins[i], OUTPUT);
  }
}

void writeBCD(const int pins[4], int value) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], (value >> i) & 1);
  }
}

void showNumber(int n) {
  writeBCD(tensPins, n / 10);
  writeBCD(unitsPins, n % 10);
}

void loop() {
  for (int n = 0; n <= 30; n++) {
    showNumber(n);
    delay(600);
  }
}
