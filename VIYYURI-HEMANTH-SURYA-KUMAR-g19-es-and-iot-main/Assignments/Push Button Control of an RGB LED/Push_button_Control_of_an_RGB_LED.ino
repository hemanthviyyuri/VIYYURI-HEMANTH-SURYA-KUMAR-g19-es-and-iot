int buttonPin = 2;
int redLedPin = 9;
int greenLedPin = 10;
int blueLedPin = 11;
int currentButtonState = LOW;
int previousButtonReading = LOW;
unsigned long buttonPressTime = 0;
unsigned long buttonReleaseTime = 0;
unsigned long debounceStartTime = 0;
int waitingForDoublePress = 0;
int doublePressDetected = 0;
int longPressDetected = 0;
void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop()
{
  unsigned long currentTime = millis();

  int buttonReading = digitalRead(buttonPin);

  if (buttonReading != previousButtonReading)
  {
    debounceStartTime = currentTime;
  }

  if (currentTime - debounceStartTime > 30)
  {
    if (buttonReading != currentButtonState)
    {
      currentButtonState = buttonReading;

      if (currentButtonState == HIGH)
      {
        buttonPressTime = currentTime;
        longPressDetected = 0;

        if (waitingForDoublePress == 1 &&
            currentTime - buttonReleaseTime <= 350)
        {
          doublePressDetected = 1;
          waitingForDoublePress = 0;
        }
      }
      else
      {
        if (longPressDetected == 0)
        {
          if (doublePressDetected == 1)
          {
            digitalWrite(redLedPin, LOW);
            digitalWrite(greenLedPin, HIGH);
            digitalWrite(blueLedPin, LOW);

            doublePressDetected = 0;
          }
          else
          {
            waitingForDoublePress = 1;
            buttonReleaseTime = currentTime;
          }
        }
      }
    }
  }

  if (currentButtonState == HIGH &&
      currentTime - buttonPressTime > 2000 &&
      longPressDetected == 0)
  {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(blueLedPin, HIGH);

    longPressDetected = 1;
    waitingForDoublePress = 0;
    doublePressDetected = 0;
  }

  if (waitingForDoublePress == 1 &&
      currentTime - buttonReleaseTime > 350)
  {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(blueLedPin, LOW);

    waitingForDoublePress = 0;
  }

  previousButtonReading = buttonReading;
}
