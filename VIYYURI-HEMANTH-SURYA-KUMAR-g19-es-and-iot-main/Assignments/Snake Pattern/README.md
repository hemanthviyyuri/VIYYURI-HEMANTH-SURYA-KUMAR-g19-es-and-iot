# Snake Pattern using 6 LED's

## Objective
To create a snake pattern using 6 LEDs using Arduino UNO R3.

## Components
- Arduino UNO R3
- 6 LEDs
- 6 × 220Ω resistors


## LED Pins
- LED 1 → Pin 2
- LED 2 → Pin 3
- LED 3 → Pin 4
- LED 4 → Pin 5
- LED 5 → Pin 6
- LED 6 → Pin 7

## Simulation
The circuit was designed and tested using Tinkercad.

## Arduino Code

```cpp
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;
int led5 = 6;
int led6 = 7;
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
}
void loop() {
  digitalWrite(led1, HIGH);
  delay(200);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(200);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(200);
  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  delay(200);
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  delay(200);
  digitalWrite(led6, LOW);
  digitalWrite(led5, HIGH);
  delay(200);
  digitalWrite(led5, LOW);
  digitalWrite(led4, HIGH);
  delay(200);
  digitalWrite(led4, LOW);
  digitalWrite(led3, HIGH);
  delay(200);
  digitalWrite(led3, LOW);
  digitalWrite(led2, HIGH);
  delay(200);
  digitalWrite(led2, LOW);
}
