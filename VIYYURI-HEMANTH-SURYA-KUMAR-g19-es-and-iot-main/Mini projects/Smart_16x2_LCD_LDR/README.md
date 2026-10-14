# Smart 16x2 LCD Character Movement with LDR-Based Mode Selection

## Mini Project – Embedded Systems and IoT

## Project Overview

This project is designed using an Arduino UNO, 16x2 I2C LCD, LDR sensor, two push buttons, LED, and buzzer.

The system has two operating modes:

- **MANUAL Mode** – The character is controlled using left and right push buttons.
- **AUTO Mode** – The character automatically moves left and right based on the LDR sensor reading.

When AUTO mode is activated:

- The LCD displays `AUTO`.
- The buzzer produces 3 beeps.
- The LED blinks 3 times.
- The character automatically moves from left to right and right to left.

When MANUAL mode is active:

- The LCD displays `MANUAL`.
- The left button moves the character one position left.
- The right button moves the character one position right.

A software debounce mechanism is also implemented to prevent multiple movements from a single button press.

---

## Project Requirements

### Hardware Components

- Arduino UNO
- 16x2 I2C LCD
- LDR (Light Dependent Resistor)
- Resistor for LDR voltage divider
- 2 × Push Buttons
- LED
- LED Resistor
- Buzzer
- Breadboard
- Jumper Wires
- USB Cable

### Software

- Arduino IDE
- Wire Library
- LiquidCrystal_I2C Library
- GitHub

---

## Circuit Connections

| Component | Arduino Pin | Function |
|-----------|-------------|----------|
| Left Push Button | D2 | Move character left |
| Right Push Button | D3 | Move character right |
| LDR | A0 | Read light intensity |
| LED | D8 | AUTO mode indication |
| Buzzer | D9 | AUTO mode indication |
| LCD SDA | A4 | I2C Data |
| LCD SCL | A5 | I2C Clock |
| LCD VCC | 5V | Power |
| LCD GND | GND | Ground |

### Push Button Connection

The push buttons use the Arduino internal pull-up resistors.

```cpp
pinMode(leftButton, INPUT);
pinMode(rightButton, INPUT);
