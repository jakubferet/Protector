void activateAlarm() {
  activeAlarm = false;
  check = false;
  change = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACTIVATING");
  lcd.setCursor(0, 1);
  lcd.print("C - CANCEL");
  countdown = count;
  while (countdown != 0 - 1) {
    currentMillis = millis();
    keypressed = customKeypad.getKey();
    active = false;
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
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      lcd.setCursor(12, 0);
      lcd.print(countdown);
      lcd.print(" ");
      tone(buzzer, 700, 100);
      countdown--;
    }
    yield();
  }
  alarmCheck();
}
