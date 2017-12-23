void postValues() {
  Serial.print("Connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
    return;
  }
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json_created = jsonBuffer.createObject();
  json_created["activate"] = activate;
  json_created["alarm"] = alarm;
  char jsonMessageBuffer[400];
  json_created.printTo(jsonMessageBuffer, sizeof(jsonMessageBuffer));
  client.println(String("POST ") + postPath+" HTTP/1.1");
  client.println(String("Host: ") + host);
  client.println("Connection: close");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(strlen(jsonMessageBuffer));
  client.println();
  client.println(jsonMessageBuffer);
  String content = client.readStringUntil('\r');
  Serial.println("Data sent");
  Serial.println(content);
  Serial.println(jsonMessageBuffer);
  if (!client.connected()) {
    Serial.println("Closing connection");
    client.stop();
  }
}
