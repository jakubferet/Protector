//function for creating temporary password for future comparison with current password
void temporaryPassword(){
  //if valid key is pressed, add it into the temporary password, print * to LCD and beep the buzzer
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

