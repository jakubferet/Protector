void setup() {
  Serial.begin(115200);
  delay(10);
  customKeypad.begin();
  lcd.begin();
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  //192.168.4.1
  WiFiManager wifiManager;
  wifiManager.autoConnect("AP-NAME", "AP-PASSWORD");
  wifiManager.setConfigPortalTimeout(120);
}
