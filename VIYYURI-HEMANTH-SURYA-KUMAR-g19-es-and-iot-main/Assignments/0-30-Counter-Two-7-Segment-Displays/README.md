# 0–30 Counter Using Two 7-Segment Displays

## Assignment Description
This project implements a digital counter from 0 to 30 using an Arduino Uno, two CD4511 BCD-to-7-segment decoder ICs, and two 7-segment displays.

The Arduino generates the counting sequence and sends separate BCD outputs for the tens and units digits. The CD4511 ICs decode these inputs to display the corresponding numbers.

## Components Required
- Arduino Uno R3
- Two CD4511 decoder ICs
- Two 7-segment displays
- Breadboards
- Jumper wires
- Current-limiting resistors

## Software
- Tinkercad Circuits
- Arduino C++

## Pin Connections

### Tens Digit
| Arduino Pin | CD4511 BCD Input |
|---|---|
| D2 | A |
| D3 | B |
| D4 | C |
| D5 | D |

### Units Digit
| Arduino Pin | CD4511 BCD Input |
|---|---|
| D6 | A |
| D7 | B |
| D8 | C |
| D9 | D |

## Working Principle
1. The counter starts at 0.
2. The Arduino separates each number into tens and units using integer division and modulo.
3. The Arduino outputs the corresponding 4-bit BCD values.
4. The CD4511 decoder ICs convert the BCD inputs into 7-segment display signals.
5. The displayed count increments every 600 milliseconds.
6. After displaying 30, the counter restarts from 0.

## Expected Output
00 → 01 → 02 → 03 → ... → 09 → 10 → ... → 29 → 30 → 00

## Program File
`0-30-Counter-Two-7-Segment-Displays.ino`

## Circuit
The circuit is implemented using an Arduino Uno, two CD4511 decoder ICs, and two 7-segment displays.

See `circuit.png` for the circuit diagram, if included.
