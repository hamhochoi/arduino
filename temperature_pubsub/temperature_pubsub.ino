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
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define PIRPIN 13  // D7

DHT dht(DHTPIN, DHTTYPE);

struct Weather {
  int h;
  int t;
};

Weather weather;
long state;
int person;
//
//char* const ssid = "HPCC-IOT";
//char* const passwd = "hpcc_iot_icse";
char *const ssid = "XuanDuc";
char *const passwd = "05061992";
char* mqtt_server = "192.168.0.106";

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
      getTemperature();
      //getMotion();
      
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_weather = jsonBuffer.createObject();
      json_weather["temperature"] = weather.t;
      json_weather["humidity"] = weather.h;
      json_weather["person"] = person;
  
      char buffer_weather[200];
      json_weather.printTo(buffer_weather, sizeof(buffer_weather));
      
      // Once connected, publish an announcement...
      client.publish("outTopic", buffer_weather);
      Serial.println(buffer_weather);
      // ... and resubscribe
      //client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      //Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(50);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIRPIN, INPUT);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, passwd);
  int wifi_ctr = 0;
  weather.h = 0;
  weather.t = 0;
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  
  };

  Serial.println("Connected successfully");
  Serial.println("IP address" + WiFi.localIP());

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  client.setServer(mqtt_server, 1883);
  
}

void loop() {
  ArduinoOTA.handle();
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    getTemperature();
    //getMotion();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& json_weather = jsonBuffer.createObject();
    json_weather["temperature"] = weather.t;
    json_weather["humidity"] = weather.h;
    json_weather["person"] = person;
    
    char buffer_weather[200];
    json_weather.printTo(buffer_weather, sizeof(buffer_weather));
    
    lastMsg = now;
    ++value;
    Serial.print("Publish message: ");
    Serial.println(buffer_weather);
    client.publish("outTopic", buffer_weather);
  }
}

void getTemperature() {
  Serial.println("Start DHT");

  weather.h = dht.readHumidity();
  weather.t = dht.readTemperature();

  if(isnan(weather.h) || isnan(weather.t)) {
    Serial.print("Failed to read from DHT");  
  } else {
    Serial.print("Humidity: ");
    Serial.print(weather.h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(weather.t);
    Serial.println(" *C");
  }
}

void getMotion() {
    state = digitalRead(PIRPIN);
    if(state == HIGH) {
      Serial.println("Motion detected!");
      person = 1;
      delay(500);
    }
    else {
      Serial.println("Motion absent!");
      person = 0;
      delay(500);
      }  
};
