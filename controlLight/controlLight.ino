#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
const char* ssid     = "baohanhhotro"; 
const char* password = "Camonquykhach";
const char* host     = "192.168.0.122"; // Your domain  
//String path          = "/wifiarduino/light.json";
String path          = "/wifiarduino";
const int pin        = 2;
void setup() {
    //pinMode(pin, OUTPUT);
    //pinMode(pin, HIGH);
    Serial.begin(115200);
  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("successfully.");
    Serial.println("IP address: " + WiFi.localIP());
}
void loop() {
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  //const int httpPort = 80;
  const int httpPort = 8080;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection to server failed");
    return;
  }
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +               "Host: " + host + "\r\n" +                "Connection: keep-alive\r\n\r\n");
  delay(500); // wait for server to respond
  // read response  
String section="header";
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print("line is: ");
    Serial.println(line);    // we’ll parse the HTML body here
    delay(2000);
    if (section=="header") { // headers..
      Serial.print(".");
      if (line=="\n") { // skips the empty space at the beginning
         section="json";
      }
    }
    else if (section=="json") {  // print the good stuff
      Serial.print("**************************************************");
      section="ignore";
      String result = line.substring(1);      // Parse JSON
      Serial.print("result is: ");
      Serial.println(result);
      delay(200);
      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }
      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed["light"], "on") == 0) {
        digitalWrite(pin, HIGH);
         Serial.println("LED ON");
      }
      else {
        digitalWrite(pin, LOW);
        Serial.println("led off");
      }
    }
  }
  Serial.println("closing connection. ");
}
