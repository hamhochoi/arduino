#include<ESP8266WiFi.h>
#include<ArduinoJson.h>

const char* ssid = "baohanhhotro";
const char* password = "Camonquykhach";

const char* host = "192.168.0.118";
const int port = 8080;
const int pin        = 2;

unsigned long previousMillis = millis();
void setup() {
  pinMode(pin, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.print("Connnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  
  }
  Serial.print(" successfully");

}

//void setup() {
//    pinMode(pin, OUTPUT);
//    //pinMode(pin, HIGH);
//    Serial.begin(115200);
//  delay(10);
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, password);
//  int wifi_ctr = 0;
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("WiFi connected");
//    Serial.println("IP address: " + WiFi.localIP());
//}

void loop() {
  WiFiClient client;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis > 5000) {

    if(!client.connect(host, port)) {
      Serial.print("Cannot connect to host: ");
      Serial.print(host);
      Serial.print(" at port ");
      Serial.println(port);
      return;
    }
  
    String url = "/watchdog?command=watchdog&uptime=";
    url += String(millis());
    url += "&ip=";
    url += WiFi.localIP().toString();
  
    // Send request to server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                "Host: " + host +"\r\n" +
                "Connection: close\r\n\r\n");
  
     unsigned long timeout = millis();
  
     while(client.available() == 0) {
      if(millis() - timeout > 5000) {
        Serial.println("Connection timeout!!!");  
        client.stop();
        return;
      } 
     }
  
    while(client.available()) {
      Serial.println("Client still alive\n");
      String line = client.readStringUntil('\r');
      Serial.print(line);  
    }
  } 
}
