//function called after the alarm is triggered
void alarmActivated() {
  check = true;
  change = false;
  alarm = "true";
  //call the postValues() function
  postValues();
  valuesCurrent = millis();
  //every few seconds, call the getValues() function
  if (valuesCurrent - valuesPrevious >= valuesInterval) {
    valuesPrevious = valuesCurrent;
    getValues();
  }
  warning = warn;
  countdown = count;
  deactivate = false;
  //print the alarm message
  if (text == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" *** ALARM *** ");
    text = 1;
  }
  //turn on the buzzer
  tone(buzzer, 1000);
  //turn on the LED
  digitalWrite(redLed, HIGH);
  printMessage = "alarm";
  deactive = true;
  //call the enterPassword() function so that the user can deactivate the alarm
  enterPassword();
}
