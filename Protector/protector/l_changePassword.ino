//function for changing the password
void changePassword() {
  k = 1;
  //read the current password from the EEPROM
  eepromRead();
  tempPass = "";
  changePass = "";
  //print text to LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Current password");
  lcd.setCursor(0,1);
  lcd.print(">");
  passChangeMode = true;
  passChanged = true;  
  passAgain = true; 
  //keep checking for keypress
  while(passChanged) {     
    keypressed = customKeypad.getKey(); 
    //if any key was pressed, call the temporaryPassword() function
    if (keypressed != 'N') {
      temporaryPassword();
    }
    //if more than six keys were pressed or if C was pressed, reset the temporary password
    if (k > 7 || keypressed == 'C') {
      tempPass = "";
      k = 1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Current password");
      lcd.setCursor(0,1);
      lcd.print(">"); 
      tone(buzzer, 600, 100);
    }
    //if * was pressed, check if the temporary password equals the current valid password
    if (keypressed == '*') {
      tone(buzzer, 600, 100);
      //if the temporary password equals the current valid password, repeat the previous
      if (tempPass == pass) {
        k = 1;
        tempPass="";
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("New password");
        lcd.setCursor(0,1);
        lcd.print(">");
        while(passChangeMode) {
          keypressed = customKeypad.getKey();
          if (keypressed != 'N') {
            temporaryPassword();
          }
          if (k > 7 || keypressed == 'C') {
            tempPass = "";
            k = 1;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("New password");
            lcd.setCursor(0,1);
            lcd.print(">");
            tone(buzzer, 600, 100);
          }
          //if * was pressed and temporary password has at least four characters, save the temporary password into a new variable
          if (keypressed == '*' && k > 4) {
            k = 1;
            tone(buzzer, 600, 100);
            changePass = tempPass;
            tempPass = "";
            passAgain = true;
            lcd.clear();
            lcd.setCursor(3,0);
            lcd.print("ONCE AGAIN");
            delay(2000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("New password");
            lcd.setCursor(0,1);
            lcd.print(">");
            //enter the new password again
            while(passAgain) {
              keypressed = customKeypad.getKey();
              if (keypressed != 'N') {
                temporaryPassword();
              }
              if (k > 7 || keypressed == 'C') {
                tempPass = "";
                k = 1;
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("New password");
                lcd.setCursor(0,1);
                lcd.print(">");
                tone(buzzer, 600, 100);
              }
              if (keypressed == '*') {
                tone(buzzer, 600, 100);
                //if the temporary password equals the new password, make the new password the current valid password,
                //call the eepromWrite() function and exit
                if (tempPass == changePass) {
                  k = 1;           
                  pass = changePass;
                  vel = pass.length();
                  eepromWrite();
                  passChangeMode = false;
                  passChanged = false;
                  passAgain = false;
                  message = 0;
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("PASSWORD CHANGED");
                  delay(2000);
                  loop();
                }
                //if the temporary password doesn't equal the new password, display error and reset the temporary password
                else if (tempPass != changePass) {
                  k = 1;
                  tempPass = "";
                  passAgain = false;
                  lcd.clear();
                  lcd.setCursor(5, 0);
                  lcd.print("WRONG!");
                  delay(2000);
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("New password");
                  lcd.setCursor(0,1);
                  lcd.print(">");
                }
              }
              yield();            
            }//end of password again while         
          }
          yield();            
        }//end of password change mode while
      }
      //if the temporary password doesn't equal the current valid password, display error and reset the temporary password
      else if (tempPass != pass) {
        k = 1;
        tempPass = "";
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("WRONG!");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Current password");
        lcd.setCursor(0,1);
        lcd.print(">");
      }
    }
    yield();
  }//end of password changed while
}
