void ledBlink() {
  ledCurrent = millis();
  if (ledCurrent - ledPrevious >= ledInterval) {
    ledPrevious = ledCurrent;
    if (ledState == LOW) {
      ledState = HIGH;
    }
    else {
      ledState = LOW;
    }
    digitalWrite(redLed, ledState);
  }
}
