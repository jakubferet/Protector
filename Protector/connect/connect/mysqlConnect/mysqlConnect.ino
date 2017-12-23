#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
IPAddress server_addr(192,168,2,196); // IP of the MySQL *server* here
char user[] = "jakub"; // MySQL user login username
char password[] = "feret"; // MySQL user login password
// Sample query
char query[] = "SELECT * FROM protector.settings";
// WiFi card example
const char* ssid  = "Feretovi";
const char* pass = "88888888";
WiFiClient client; // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client);
int countdown = 0;
int warning = 0;
int ledPin = 2;
String activate;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  // Begin WiFi section
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
  // End WiFi section
  Serial.println("Connecting to database...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(500);
  }
  else
    Serial.println("Connection failed.");
}

void loop() {
  if (conn.connected()) {
    row_values *row = NULL;
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    // Execute the query
    cur_mem->execute(query);
    // Fetch the columns (required) but we don't use them.
    column_names *columns = cur_mem->get_columns();
    // Read the row (we are only expecting the one)
    do {
      row = cur_mem->get_next_row();
      if (row != NULL) {
        warning = atol(row->values[4]);
        countdown = atol(row->values[3]);
        activate = row->values[1];
      } 
    }while (row != NULL);
    // Deleting the cursor also frees up memory used
    delete cur_mem;
    // Show the result
    Serial.print("Countdown = ");
    Serial.println(countdown);
    Serial.print("Warning = ");
    Serial.println(warning);
    Serial.print("Activate = ");
    Serial.println(activate);
    if (activate == "true")
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);
  } 
  else {
    conn.close();
    Serial.println("Connecting...");
    if (conn.connect(server_addr, 3306, user, password)) {
      delay(500);
      Serial.println("Successful reconnect!");
    } 
    else {
      Serial.println("Cannot reconnect!");
    }
  }  
  delay(1000);
}
