//function for deactivating the alarm or the countdown
void deactivateAlarm(){
  deactive = false;
  message = 0;
  //buzzer silent
  noTone(buzzer);
  //LED off
  digitalWrite(redLed, LOW);
  //print text to LCD for one second
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("DEACTIVATED");
  delay(1000);
  //call the loop() function
  loop();
  return;
}
