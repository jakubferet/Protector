void alarmActivated() {
  check = true;
  change = false;
  alarm = "true";
  postValues();
  valuesCurrent = millis();
  if (valuesCurrent - valuesPrevious >= valuesInterval) {
    valuesPrevious = valuesCurrent;
    getValues();
  }
  warning = warn;
  countdown = count;
  deactivate = false;
  if (text == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" *** ALARM *** ");
    text = 1;
  }
  tone(buzzer, 1000);
  digitalWrite(redLed, HIGH);
  activateMessage = false;
  warningMessage = false;
  cancelMessage = false;
  alarmMessage = true;
  deactive = true;
  enterPassword();
}
