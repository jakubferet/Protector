void getValues() {
  if(check == true){
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
    client.print(String("GET ") + getPath + " HTTP/1.1\r\n" +
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
    String section = "header";
    while (client.available()) {
      String content = client.readStringUntil('\r');
      //Serial.print(content);
      // we’ll parse the HTML body here
      if (section == "header") { // headers..
        Serial.print(".");
        if (content.charAt(1) == '9') {
          section = "json";
        }
      }
      else if (section == "json") { // print the good stuff
        Serial.println("");
        section = "ignore";
        String json = content;
        // Parse JSON
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& json_parsed = jsonBuffer.parseObject(json);
        if (!json_parsed.success()) {
          Serial.println("Parsing failed!");
          return;
        }
        countdown = json_parsed["settings"]["countdown"];
        warning = json_parsed["settings"]["warning"];
        count = json_parsed["settings"]["countdown"];
        warn = json_parsed["settings"]["warning"];
        activate = (json_parsed["settings"]["activate"]).as<String>();
        countdown = count;
        warning = warn;
  
        // Print values.
        //Serial.println(json);
        Serial.println("Data received");
        Serial.print("countdown: ");
        Serial.println(countdown);
         Serial.print("warning: ");
        Serial.println(warning);
         Serial.print("activate: ");
        Serial.println(activate);
      }
    }
    if (!client.connected()) {
      Serial.println("Closing connection");
      client.stop();
    }
  }
}
