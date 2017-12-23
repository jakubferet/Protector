void deactivateAlarm(){
  deactive = false;
  message = 0;
  noTone(buzzer);
  digitalWrite(redLed, LOW);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("DEACTIVATED");
  delay(1000);
  loop();
  return;
}
