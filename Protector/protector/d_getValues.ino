//function for getting JSON data from the server with GET request, parsing them and saving them into variables
void getValues() {
  if(check == true){
    //connect to the server
    Serial.print("Connecting to ");
    Serial.println(host);
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("Connection failed!");
      return;
    }
    //send GET request to the server
    client.print(String("GET ") + getPath + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    //if the client isn't available for more than five seconds, the error message is displayed and the function is stopped
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout!");
        client.stop();
        return;
      }
    }//end of while
    //read response from the server
    String section = "header";
    //keep repeating while client is available
    while (client.available()) {
      String content = client.readStringUntil('\r');
      //Serial.print(content);
      //get rid of the header
      if (section == "header") {
        Serial.print(".");
        if (content.charAt(1) == '9') {
          section = "json";
        }
      }
      else if (section == "json") {
        Serial.println("");
        section = "ignore";
        String json = content;
        //parse JSON
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& json_parsed = jsonBuffer.parseObject(json);
        if (!json_parsed.success()) {
          Serial.println("Parsing failed!");
          return;
        }//save values into variables
        countdown = json_parsed["settings"]["countdown"];
        warning = json_parsed["settings"]["warning"];
        count = json_parsed["settings"]["countdown"];
        warn = json_parsed["settings"]["warning"];
        activate = (json_parsed["settings"]["activate"]).as<String>();
        countdown = count;
        warning = warn;
        //print values
        //Serial.println(json);
        Serial.println("Data received");
        Serial.print("countdown: ");
        Serial.println(countdown);
         Serial.print("warning: ");
        Serial.println(warning);
         Serial.print("activate: ");
        Serial.println(activate);
      }
    }//end of while
    //close connection
    if (!client.connected()) {
      Serial.println("Closing connection");
      client.stop();
    }
  }
}
