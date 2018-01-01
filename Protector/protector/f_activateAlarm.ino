//function for counting the time until alarm activation
void activateAlarm() {
  activeAlarm = true;
  check = false;
  change = false;
  //print text to LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACTIVATING");
  lcd.setCursor(0, 1);
  lcd.print("C - CANCEL");
  countdown = count;
  //count the time until it's 0, then call function alarmCheck()
  while (countdown != 0 - 1) {
    currentMillis = millis();
    keypressed = customKeypad.getKey();
    active = false;
    //if the user presses C, the enterPassword() function is called so that the user can cancel the countdown
    if (keypressed == 'C') {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("CANCEL");
      warning = 0 - 1;
      activateMessage = false;
      warningMessage = false;
      alarmMessage = false;
      cancelMessage = true;
      back = true;
      deactivate = true;
      enterPassword();
      return;
    }
    //every second the countdown decreases and buzzer beeps
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      lcd.setCursor(12, 0);
      lcd.print(countdown);
      lcd.print(" ");
      tone(buzzer, 700, 100);
      countdown--;
    }
    yield();
  }//end of while
  alarmCheck();
}
