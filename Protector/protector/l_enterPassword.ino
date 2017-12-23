void enterPassword() {
  int attempt = 3;
  int k = 9;
  tempPass = "";
  activated = true;
  lcd.setCursor(0, 1);
  lcd.print("Password:");
  while (activated) {
    while (warning != 0 - 1 || countdown != 0 - 1) {
      keypressed = customKeypad.getKey();
      if(keypressed == 'B' && change == true){
        tone(buzzer, 600, 100);
        changePassword();  
      }
      valuesCurrent = millis();
      if (valuesCurrent - valuesPrevious >= valuesInterval) {
        valuesPrevious = valuesCurrent;
        getValues();
      }
      if (activate == "true" && active == true && alarm == "false") {
          deactivate = false;
          activated = false;
          message = 0;
          text = 0;
          activateAlarm();
      }
      else if(activate == "false" && deactive == true){
        alarm = "false";
        postValues();
        deactivateAlarm(); 
      }
      if (deactivate == true) {
        check = false;
        currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
          previousMillis = currentMillis;
          if (back == true) {
            lcd.setCursor(12, 0);
            lcd.print(countdown);
            lcd.print(" ");
            tone(buzzer, 700, 100);
            countdown--;
          }
          else {
            ledBlink();
            lcd.setCursor(13, 0);
            lcd.print(warning);
            lcd.print(" ");
            tone(buzzer, 700, 100);
            warning--;
          }
        }
      }
      if (keypressed != 'N') {
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
          tempPass += keypressed;
          lcd.setCursor(k, 1);
          lcd.print("*");
          if (alarm == "false") {
            tone(buzzer, 500, 100);
          }
          k++;
        }
      }
      if (k > 15 || keypressed == 'C') {
        if (alarm == "false") {
          tone(buzzer, 600, 100);
        }
        k = 9;
        tempPass = "";
        lcd.clear();
        if (activateMessage == true) {
          lcd.setCursor(1, 0);
          lcd.print("ACTIVATE ALARM");
        }
        else if (warningMessage == true) {
          lcd.setCursor(4, 0);
          lcd.print("WARNING");
        }
        else if (alarmMessage == true) {
          lcd.setCursor(0, 0);
          lcd.print(" *** ALARM *** ");
        }
        else if (cancelMessage == true) {
          lcd.setCursor(5, 0);
          lcd.print("CANCEL");
        }
        lcd.setCursor(0, 1);
        lcd.print("Password:");
      }
      if (keypressed == '*') {
        if (alarm == "false") {
          tone(buzzer, 600, 100);
        }
        if (tempPass == pass) {
          if(activate == "true"){
            activate = "false";
          }        
          else if (activate == "false"){
            activate = "true";
          }
          alarm = "false";
          postValues();
          activated = false;
          deactivate = false;
          message = 0;
          text = 0;
          if (activeAlarm == true) {
            activateAlarm();
          }
          else {
            deactivateAlarm();
          }
        }
        else if (tempPass != pass) {
          k = 9;
          tempPass = "";
          attempt--;
          lcd.clear();
          lcd.setCursor(5, 0);
          lcd.print("WRONG!");
          if (activateMessage == false && alarmMessage == false) {
            lcd.setCursor(0, 1);
            lcd.print("ATTEMPTS:");
            lcd.setCursor(10, 1);
            lcd.print(attempt);
            if (attempt == 0) {
              alarmActivated();
            }
          }
          delay(2000);
          lcd.clear();
          if (activateMessage == true) {
            lcd.setCursor(1, 0);
            lcd.print("ACTIVATE ALARM");
          }
          else if (warningMessage == true) {
            lcd.setCursor(4, 0);
            lcd.print("WARNING");
          }
          else if (alarmMessage == true) {
            lcd.setCursor(0, 0);
            lcd.print(" *** ALARM *** ");
          }
          else if (cancelMessage == true) {
            lcd.setCursor(5, 0);
            lcd.print("CANCEL");
          }
          lcd.setCursor(0, 1);
          lcd.print("Password:");
        }
      }
      yield();
    }
    if (back == true) {
      alarmCheck();
    }
    else {
      alarmActivated();
    }
    yield();
  }
}
