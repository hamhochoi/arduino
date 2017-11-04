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

#define DHTPIN 2
#define DHTTYPE DHT11

struct Weather {
  float h;
  float t;
};

Weather weather;

char* const ssid = "HPCC-IOT";
char* const passwd = "hpcc_iot_icse";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
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
  dht.begin();
  delay(100);
}

void loop() {
  getTemperature();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& json_parsed = jsonBuffer.createObject();

  json_parsed["sensorType"] = "DHT11";
  json_parsed["temperature"] = weather.t;
  json_parsed["humidity"] = weather.h;
  
  char JSONMessageBuffer[300];
  json_parsed.prettyPrintTo(JSONMessageBuffer, sizeof(JSONMessageBuffer));
  Serial.println(JSONMessageBuffer);

  HTTPClient http;

  http.begin("http://192.168.60.200:8080/weather");
  http.addHeader("Content-Type", "application/json");
  
  int httpCode = http.POST(JSONMessageBuffer);
  String payload = http.getString();

  Serial.print("HttpCode: ");
  Serial.println(httpCode);
  Serial.print("Payload: ");
  Serial.println(payload);
  // Wait a bit before scanning again
  delay(10000);
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
