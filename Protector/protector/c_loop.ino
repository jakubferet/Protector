//default function loop() keeps repeating
void loop() { 
  //over the air transfer
  if(ota == true){ 
    //after the reboot, over the air transfer can be used for certain time
    while (otaTransfer < otaTime) {
      otaCurrent = millis();
      if (otaCurrent - otaPrevious >= otaInterval) {
        otaPrevious = otaCurrent;
        otaTransfer++;
      }
      ArduinoOTA.handle();
      yield();
    }//end of while
    //when over the air transfer ended, the ledBlink() function is called and program can continue
    ledBlink();
    ota = false;
  }
  //get pressed key
  keypressed = customKeypad.getKey();
  printMessage = "activate";
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
