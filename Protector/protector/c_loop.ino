//default function loop() keeps repeating
void loop() {
  //get pressed key
  keypressed = customKeypad.getKey();
  warningMessage = false;
  alarmMessage = false;
  cancelMessage = false;
  activateMessage = true;
  activeAlarm = false;
  check = true;
  change = true; 
  active = true;
  //buzzer silent
  noTone(buzzer);
  //LED off
  digitalWrite(redLed, LOW);
  //print text to LCD
  if (message == 0) {
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("ACTIVATE ALARM");
    message = 1;
  }
  //call function enterPassword()
  enterPassword();
  /*Serial.print(distance);
    Serial.print(" cm ");
    Serial.println();
    delay(100);*/
}
