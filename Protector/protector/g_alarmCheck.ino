//Function uses the getDistance() function to detect changes in the measured distance.
//If they occur, warning message is printed and enterPassword() function is called.
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
  //keep measuring the distance
  while (danger == false) {
    //every few seconds call the getValues() function
    valuesCurrent = millis();
    if (valuesCurrent - valuesPrevious >= valuesInterval) {
      valuesPrevious = valuesCurrent;
      getValues();
    }
    if(activate == "false"){
      deactivateAlarm();  
    }
    currentDistance = getDistance() + 20;
    //check if the measured distance changed
    if (currentDistance < initialDistance) {
      danger = true;
      check = false;
      warning = warn;
      countdown = 0 - 1;
      //display warning message and call function enterPassword()
      while (warning != 0 - 1) {
        if (message == 0) {
          lcd.clear();
          lcd.setCursor(4, 0);
          lcd.print("WARNING");
          message = 1;
        }
        active = false;
        printMessage = "warning";
        deactivate = true;
        enterPassword();
        yield();
      }//end of while
      alarmActivated();
    }
    yield();
  }//end of while
}
