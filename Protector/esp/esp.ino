#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial espSerial =  SoftwareSerial(8,9);      // arduino RX pin=2  arduino TX pin=3    connect the arduino RX pin to esp8266 module TX pin   -  connect the arduino TX pin to esp8266 module RX pin

String ssid     = "Feretovi";
String password = "88888888";

const char* host = "192.168.2.196";
String path = "/protector/protector/www/json/json";

int countdown = 0;
int warning = 0;
int ledPin = 2;

boolean DEBUG=true;


void showResponse(int waitTime){
    long t=millis();
    char c;
    while (t+waitTime>millis()){
      if (espSerial.available()){
        c=espSerial.read();
        if (DEBUG) Serial.print(c);
      }
    }
                   
}

void setup() {                
  DEBUG=true;           // enable debug serial
  Serial.begin(9600); 
  
  espSerial.begin(9600);  // enable software serial
                          // Your esp8266 module's speed is probably at 115200. 
                          // For this reason the first time set the speed to 115200 or to your esp8266 configured speed 
                          // and upload. Then change to 9600 and upload again
  
  /*espSerial.println("AT+UART_DEF=9600,8,1,0,0");    // Enable this line to set esp8266 serial speed to 9600 bps
  showResponse(1000);*/
  
  /*espSerial.println("AT+RST");         // Enable this line to reset the module;
  showResponse(1000);*/

  espSerial.println("AT+CWMODE=1");   // set esp8266 as client
  showResponse(1000);

  espSerial.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");  // set your home router SSID and password
  showResponse(5000);

  if (DEBUG)  
    Serial.println("Setup completed");
}


/*void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);  
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}*/

void loop() {
  Serial.print("connecting to ");
  Serial.println(host);  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // This will send the request to the server
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");          
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout!");
      client.stop();
      return;
    }
  }  
    // read response
  String section="header";
  while(client.available()){
    String content = client.readStringUntil('\r');
    // Serial.print(line);
    // we’ll parse the HTML body here
    if (section=="header") { // headers..
      Serial.print(".");
      if (content=="\n") { // skips the empty space at the beginning 
        section="json";
      }
    }
    else if (section=="json") {  // print the good stuff
      Serial.println("");
      section="ignore";
      String json = content.substring(1);

      // Parse JSON
      StaticJsonBuffer<400> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success()){
        Serial.println("Parsing failed!");
        return;
      }
      countdown = json_parsed["settings"]["countdown"];
      warning = json_parsed["settings"]["warning"];
      String activate = json_parsed["settings"]["activate"];

      // Print values.
      //Serial.println(json);
      Serial.println(countdown);
      Serial.println(warning);
      Serial.println(activate);

      if (activate == "true")
        digitalWrite(ledPin, HIGH);
      else
        digitalWrite(ledPin, LOW);
    }
  }
  Serial.println("Closing connection"); 
  delay(1000);
}






