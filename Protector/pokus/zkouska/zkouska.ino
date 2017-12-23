#include <LiquidCrystal_I2C.h>

#define TRIGGER_PIN  14 // D5
#define ECHO_PIN     12 //D6 
#define redLed 13 //D7
#define buzzer 15 //D8

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin (115200);
  lcd.begin(16,2); 
  lcd.init();
  lcd.backlight();
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(buzzer, OUTPUT); 
  pinMode(redLed, OUTPUT);
 
}

void loop() {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("ACTIVATE ALARM"); 
  double duration, distance;
  
  digitalWrite(TRIGGER_PIN, LOW);  // Get Start
  delayMicroseconds(2); // stable the line 
  digitalWrite(TRIGGER_PIN, HIGH); // sending 10 us pulse
  delayMicroseconds(10); // delay 
  
  digitalWrite(TRIGGER_PIN, LOW); // after sending pulse wating to receive signals 
  
  duration = pulseIn(ECHO_PIN, HIGH); // calculating time 
  
  distance = (duration/2) / 29.1; // single path 
  
  //Serial.print(distance);
  
  //Serial.println(" cm");

  char keypadPin = A0;
  int value = analogRead(keypadPin);
  Serial.println(value);
  
  delay(100);
  if(distance<20){
    tone(buzzer, 700); 
    digitalWrite(redLed, HIGH); 
  }
}
