void changePassword() {
  lcd.clear();
  int i=1;
  tempPass = "";
  lcd.setCursor(0,0);
  lcd.print("Current password");
  lcd.setCursor(0,1);
  lcd.print(">");
  passChangeMode = true;
  passChanged = true;   
  while(passChanged) {      
    keypressed = customKeypad.getKey();
    if (keypressed != NO_KEY){
      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
          keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
          keypressed == '8' || keypressed == '9' ) {
       tempPass += keypressed;
       lcd.setCursor(i,1);
       lcd.print("*");
       i++;
       tone(buzzer, 500, 100);
      }
    }
    if (i > 7 || keypressed == 'C') {
      tempPass = "";
      i=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Current password");
      lcd.setCursor(0,1);
      lcd.print(">"); 
      tone(buzzer, 600, 100);
    }
    if ( keypressed == '*') {
      if (tempPass == pass) {
        i=1;
        tone(buzzer, 600, 100);
        tempPass="";
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("New password");
        lcd.setCursor(0,1);
        lcd.print(">");
        while(passChangeMode) {
          keypressed = customKeypad.getKey();
          if (keypressed != NO_KEY){
            if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                keypressed == '8' || keypressed == '9' ) {
              tempPass += keypressed;
              lcd.setCursor(i,1);
              lcd.print("*");
              i++;
              tone(buzzer, 500, 100);
            }
          }
          if (i > 7 || keypressed == 'C') {
            tempPass = "";
            i=1;
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("New password");
            lcd.setCursor(0,1);
            lcd.print(">");
            tone(buzzer, 600, 100);
          }
          if ( keypressed == '*') {
            i=1;
            tone(buzzer, 600, 100);
            pass = tempPass;
            passChangeMode = false;
            passChanged = false;
            message = 0;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("PASSWORD CHANGED");
            delay(2000);
            loop();
          }
          yield();            
        }
      }
      else if (tempPass != pass) {
        i = 1;
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
  }
}
