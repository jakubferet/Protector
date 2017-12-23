#include <WiFiManager.h>
#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define buzzer 15
#define redLed 13
#define trigPin 14
#define echoPin 12
const char* host = "protector.sspu-opava.eu";
String getPath = "/json/json";
String postPath = "/values/values";
long duration;
int distance;
int initialDistance;
int currentDistance;
int i;
int countdown = 10;
int warning = 10;
int count = 10;
int warn = 10;
String activate;
String alarm = "false";
boolean active = true;
boolean deactive = false;
int message = 0;
int text = 0;
String pass = "1234";
String tempPass;
boolean activated;
boolean activeAlarm = false;
boolean passChangeMode = false;
boolean passChanged = false;
boolean change = true;
boolean danger = false;
boolean deactivate = false;
boolean back = false;
boolean check = true;
boolean activateMessage = false;
boolean warningMessage = false;
boolean alarmMessage = false;
boolean cancelMessage = false;
int ledState = LOW;
unsigned long ledPrevious = 0;
unsigned long ledCurrent;
const long ledInterval = 50;
unsigned long previousMillis = 0;
unsigned long currentMillis;
const long interval = 1000;
unsigned long valuesPrevious = 0;
unsigned long valuesCurrent;
const long valuesInterval = 10000;
char keypressed;
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad
Keypad_I2C customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, 0x21);
LiquidCrystal_I2C lcd(0x27, 16, 2);
