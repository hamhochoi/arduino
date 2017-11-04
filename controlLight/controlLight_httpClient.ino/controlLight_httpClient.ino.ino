#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "XuanDuc";
const char* password = "05061992";

const char* host = "192.168.0.104";
int port = 8080;
String path          = "/";


void setup() {
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
  HTTPClient http;
  http.begin(host, port, path);
  Serial.println("Connect to host successfully");
  int httpCode = http.GET();
  if(httpCode) {
    if(httpCode == 200) {
      String payload = http.getString();
      Serial.print("payload: ");
      Serial.println(payload);  
    } else {
      Serial.print("httpCode: ");
      Serial.println(httpCode);  
    }
  } else {
    Serial.println("httpCode does not exists");  
  }

  Serial.println("Closing connect");
  http.end();
  WiFi.disconnect();
}
