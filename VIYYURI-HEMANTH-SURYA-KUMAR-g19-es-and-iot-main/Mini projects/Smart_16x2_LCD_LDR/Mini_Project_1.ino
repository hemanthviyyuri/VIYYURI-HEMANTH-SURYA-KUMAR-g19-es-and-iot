#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x26, 16, 2);
const int leftButton = 2;
const int rightButton = 3;
const int ldrPin = A0;
const int ledPin = 8;
const int buzzerPin = 9;
const int threshold = 500; 
int position = 0;
int direction = 1;
bool previousAuto = false;
unsigned long lastMove = 0;
const unsigned long moveDelay = 200; 
byte character[8] = {
  B00100,
  B01010,
  B01010,
  B00100,
  B11111,
  B00100,
  B01010,
  B10001
};
int lastReading[2] = {HIGH, HIGH};
int stableState[2] = {HIGH, HIGH};
unsigned long lastDebounce[2] = {0, 0};
bool buttonPressed(int index, int pin) {
  int reading = digitalRead(pin);
  if (reading != lastReading[index]) {
    lastDebounce[index] = millis();
    lastReading[index] = reading;
  }
  if (millis() - lastDebounce[index] >= 20) {
    if (reading != stableState[index]) {
      stableState[index] = reading;
      if (stableState[index] == LOW) {
        return true;
      }
    }
  }
  return false;
}
void showCharacter() {
  lcd.setCursor(0, 0);
  lcd.print("                "); 
  lcd.setCursor(position, 0);
  lcd.write(byte(0));           
}
void automaticSignal() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);
    delay(80);
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(60); 
  }
}
void setup() {
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, character);
  lcd.setCursor(0, 0);
  lcd.print("MINI PROJECT 1");
  delay(800);
  lcd.clear();
  showCharacter();
}
void loop() {
  int lightValue = analogRead(ldrPin);
  bool autoMode = (lightValue >= threshold);
 if (autoMode != previousAuto) {
    previousAuto = autoMode;    
    lcd.setCursor(0, 1);
    if (autoMode) {
      lcd.print("AUTO   ");
      showCharacter();
      automaticSignal(); 
      lastMove = millis();
    } else {
      lcd.print("MANUAL   ");
      showCharacter();
    }
  }
  if (autoMode) {
    if (millis() - lastMove >= moveDelay) {
      lastMove = millis();
      position += direction;
      if (position >= 15) {
        position = 15;
        direction = -1;
      }
      if (position <= 0) {
        position = 0;
        direction = 1;
      }
      showCharacter();
    }
  } else {
        if (buttonPressed(0, leftButton)) {
      if (position > 0) {
        position--;
        showCharacter();
      }
    }
    if (buttonPressed(1, rightButton)) {
      if (position < 15) {
        position++;
        showCharacter();
      }
    }
  }
}
