void alarmCheck() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM ACTIVATED!");
  tone(buzzer, 1000, 100);
  initialDistance = getDistance();
  danger = false;
  back = false;
  check = true;
  change = false;
  while (danger == false) {
    valuesCurrent = millis();
    if (valuesCurrent - valuesPrevious >= valuesInterval) {
      valuesPrevious = valuesCurrent;
      getValues();
    }
    if(activate == "false"){
      deactivateAlarm();  
    }
    currentDistance = getDistance() + 30;
    if (currentDistance < initialDistance) {
      danger = true;
      check = false;
      warning = warn;
      countdown = 0 - 1;
      while (warning != 0 - 1) {
        if (message == 0) {
          lcd.clear();
          lcd.setCursor(4, 0);
          lcd.print("WARNING");
          message = 1;
        }
        active = false;
        activateMessage = false;
        alarmMessage = false;
        cancelMessage = false;
        warningMessage = true;
        deactivate = true;
        enterPassword();
        yield();
      }
      alarmActivated();
    }
    yield();
  }
}
