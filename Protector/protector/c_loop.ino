void loop() {
  keypressed = customKeypad.getKey();
  warningMessage = false;
  alarmMessage = false;
  cancelMessage = false;
  activateMessage = true;
  activeAlarm = true;
  check = true;
  change = true; 
  active = true;
  noTone(buzzer);
  digitalWrite(redLed, LOW);
  if (message == 0) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("ACTIVATE ALARM");
    message = 1;
  }
  enterPassword();
  /*Serial.print(distance);
    Serial.print(" cm ");
    Serial.println();
    delay(100);*/
}
