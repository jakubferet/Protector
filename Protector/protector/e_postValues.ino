//function for encoding variables into JSON and sending them to the web server with POST request
void postValues() {
  //connect to the server
  Serial.print("Connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
    return;
  }
  //create JSON
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json_created = jsonBuffer.createObject();
  json_created["activate"] = activate;
  json_created["alarm"] = alarm;
  char jsonMessageBuffer[200];
  json_created.printTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));
  //send POST request to the server
  client.println(String("POST ") + postPath+" HTTP/1.1");
  client.println(String("Host: ") + host);
  client.println("Connection: close");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(strlen(jsonMessageBuffer));
  client.println();
  client.println(jsonMessageBuffer);
  //print the result
  String content = client.readStringUntil('\r');
  Serial.println("Data sent");
  Serial.println(content);
  Serial.println(jsonMessageBuffer);
  if (!client.connected()) {
    Serial.println("Closing connection");
    client.stop();
  }
}
