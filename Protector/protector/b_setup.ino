//default function setup() always called at the beginning
void setup() {
  // serial monitor inicialization
  Serial.begin(115200);
  //EEPROM inicialization
  EEPROM.begin(512);  
  delay(10);
  //eepromWrite();
  eepromRead();
  // keypad inicialization
  customKeypad.begin();
  //LCD display inicialization
  lcd.begin();
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  //WiFi manager
  //192.168.4.1
  WiFiManager wifiManager;
  wifiManager.setConfigPortalTimeout(120);
  wifiManager.autoConnect("AP-NAME", "AP-PASSWORD");
}
