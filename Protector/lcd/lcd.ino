#include <Wire.h>
#include <LiquidCrystal_I2C.h> // includes the LiquidCrystal Library 

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Hello, World!");

}

void loop() {
  // put your main code here, to run repeatedly:

}
