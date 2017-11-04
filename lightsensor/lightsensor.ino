/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#include "ESP8266WiFi.h"
#include "WiFiClient.h"
#include "ESP8266HTTPClient.h"
#include "DHT.h"
#include "ArduinoJson.h"
#include "PubSubClient.h"

#define PIRPIN D4  // 

char* const ssid = "XuanDuc";
char* const passwd = "05061992";
char* mqtt_server = "192.168.0.106";

int sensorValue ;

WiFiClient esp8266Client;
PubSubClient client(esp8266Client);

long lastMsg = 0;
char msg[50];
int value = 0;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      //client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      //Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(50);
    }o
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIRPIN, INPUT);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, passwd);
  int wifi_ctr = 0;
 
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  
  };

  Serial.println("Connected successfully");
  Serial.println("IP address" + WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    getLight();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json_weather = jsonBuffer.createObject();
    json_weather["light"] = sensorValue;
    
    char buffer_weather[200];
    json_weather.printTo(buffer_weather, sizeof(buffer_weather));
    
    lastMsg = now;
    ++value;
    Serial.print("Publish message: ");
    Serial.println(buffer_weather);
    client.publish("outTopic", buffer_weather);
  }
}

void getLight() {
  sensorValue = analogRead(D4);  
}
