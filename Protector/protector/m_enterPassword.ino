//password input and validation function 
void enterPassword() {
  int attempt = 3;
  k = 9;
  //read the current password from the EEPROM
  eepromRead();
  tempPass = "";
  activated = true;
  lcd.setCursor(0, 1);
  lcd.print("Password:");
  //keep repeating while activated is true
  while (activated) {
    //keep repeating until warning or countdown is 0
    while (warning != 0 - 1 || countdown != 0 - 1) {
      keypressed = customKeypad.getKey();
      //if B was pressed, call the changePassword() function
      if(keypressed == 'B' && change == true){
        tone(buzzer, 600, 100);
        changePassword();  
      }
      //every few seconds call the getValues() function
      valuesCurrent = millis();
      if (valuesCurrent - valuesPrevious >= valuesInterval) {
        valuesPrevious = valuesCurrent;
        getValues();
      }
      //if activate is true and alarm isn't already activated, call the activateAlarm() function
      if (activate == "true" && active == true && alarm == "false") {
          deactivate = false;
          activated = false;
          message = 0;
          text = 0;
          activateAlarm();
      }
      //id activate is false, call the deactivateAlarm() function
      else if(activate == "false" && deactive == true){
        alarm = "false";
        postValues();
        deactivateAlarm(); 
      }
      //if deactivate is true, keep beeping, blinking and decreasing the countdown and the warning variable every second
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
      //if any key was pressed, call the temporaryPassword() function
      if (keypressed != 'N') {
        temporaryPassword();
      }
      //if more than six keys were pressed or if C was pressed, reset the temporary password
      if (k > 15 || keypressed == 'C') {
        if (alarm == "false") {
          tone(buzzer, 600, 100);
        }
        k = 9;
        tempPass = "";
        lcd.clear();
        if (printMessage == "activate") {
          lcd.setCursor(1, 0);
          lcd.print("ACTIVATE ALARM");
        }
        else if (printMessage == "warning") {
          lcd.setCursor(4, 0);
          lcd.print("WARNING");
        }
        else if (printMessage == "alarm") {
          lcd.setCursor(0, 0);
          lcd.print(" *** ALARM *** ");
        }
        else if (printMessage == "cancel") {
          lcd.setCursor(5, 0);
          lcd.print("CANCEL");
        }
        lcd.setCursor(0, 1);
        lcd.print("Password:");
      }
      //if * was pressed, check if the temporary password equals the current valid password
      if (keypressed == '*') {
        if (alarm == "false") {
          tone(buzzer, 600, 100);
        }
        //if the temporary password equals the current valid password
        if (tempPass == pass) {
          if(activate == "true"){
            activate = "false";
          }        
          else if (activate == "false"){
            activate = "true";
          }
          alarm = "false";
          //call the postValues() function
          postValues();
          activated = false;
          deactivate = false;
          message = 0;
          text = 0;
          //if the alarm isn't already activated, call the activateAlarm() function
          if (activeAlarm == false) {
            activateAlarm();
          }
          //if the alarm already is activated, call the deactivateAlarm() function
          else {
            deactivateAlarm();
          }
        }
        //if the temporary password doesn't equal the current valid password, display error, reset the temporary password and decrease the number of remaining attempts
        else if (tempPass != pass) {
          k = 9;
          tempPass = "";
          attempt--;
          lcd.clear();
          lcd.setCursor(5, 0);
          lcd.print("WRONG!");
          if (printMessage != "activate" && printMessage != "alarm") {
            lcd.setCursor(0, 1);
            lcd.print("ATTEMPTS:");
            lcd.setCursor(10, 1);
            lcd.print(attempt);
            //if there are no attempts left, call the alarmActivated() function
            if (attempt == 0) {
              alarmActivated();
            }
          }
          delay(2000);
          lcd.clear();
          if (printMessage == "activate") {
            lcd.setCursor(1, 0);
            lcd.print("ACTIVATE ALARM");
          }
          else if (printMessage == "warning") {
            lcd.setCursor(4, 0);
            lcd.print("WARNING");
          }
          else if (printMessage == "alarm") {
            lcd.setCursor(0, 0);
            lcd.print(" *** ALARM *** ");
          }
          else if (printMessage == "cancel") {
            lcd.setCursor(5, 0);
            lcd.print("CANCEL");
          }
          lcd.setCursor(0, 1);
          lcd.print("Password:");
        }
      }
      yield();
    }//end of while
    //when the countdown is 0, call the alarmCheck() function
    if (back == true) {
      alarmCheck();
    }
    //when the warning is 0, call the alarmActivated() function
    else {
      alarmActivated();
    }
    yield();
  }//end of while activated
}
