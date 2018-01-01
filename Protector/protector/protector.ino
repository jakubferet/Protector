//libraries
#include <ESP8266WiFi.h> //ESP8266 WiFi connection
#include <WiFiManager.h> //ESP8266 WiFi manager - automatic connection
#include <DNSServer.h> //needed for WiFi manager    
#include <ESP8266WebServer.h> //needed for WiFi manager
#include <EEPROM.h> //storing data in EEPROM
#include <ArduinoJson.h> //json encoding and decoding
#include <Keypad_I2C.h> //I2C keypad
#include <Keypad.h> //needed for I2C keypad
#include <Wire.h> //needed for display and keypad
#include <LiquidCrystal_I2C.h> //I2C display
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
int k;
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
int address = 0;
String pass;
int vel = 0;
String tempPass;
String changePass;
boolean activated;
boolean activeAlarm = true;
boolean passChangeMode = false;
boolean passChanged = false;
boolean passAgain = false;
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
//keypad declaration
char keypressed;
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {4, 5, 6, 7};
Keypad_I2C customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, 0x21);
//LCD display inicialization
LiquidCrystal_I2C lcd(0x27, 16, 2);
