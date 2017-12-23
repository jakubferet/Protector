#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "Feretovi";
const char* password = "88888888";

const char* host = "192.168.2.196";
String path = "/protector/protector/www/json/json";

int countdown = 0;
int warning = 0;
int ledPin = 2;

void setup() {
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
}

void loop() {
  Serial.print("Connecting to ");
  Serial.println(host);  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
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

