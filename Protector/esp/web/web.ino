#include <WiFiEsp.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial espSerial = SoftwareSerial(8, 9); // RX, TX

const char* ssid     = "Feretovi";
const char* password = "88888888";

const char* host = "192.168.2.196";
String path = "/protector/protector/www/json/json";

int countdown = 0;
int warning = 0;
int ledPin = 2;

void setup() {
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  espSerial.begin(9600);
  // initialize ESP module
  WiFi.init(&espSerial);
  pinMode(ledPin, OUTPUT);
  // We start by connecting to a WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(ssid);  
    WiFi.begin(ssid, password); 
  } 
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("connecting to ");
  Serial.println(host);  
  // Use WiFiClient class to create TCP connections
  WiFiEspClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // This will send the request to the server
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");          
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
    Serial.print(content);
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
      const size_t bufferSize = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(5) + 140;
      DynamicJsonBuffer jsonBuffer(bufferSize);
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
  if (!client.connected()) {
    Serial.println();
    Serial.println("Closing connection");
    client.stop();
  }
}


