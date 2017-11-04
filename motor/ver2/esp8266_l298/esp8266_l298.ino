#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "ArduinoJson.h"

char *ssid = "XuanDuc";
char *passwd = "05061992";

char *url = "http://192.168.0.106:8080/direction";

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, passwd);
    int wifi_ctr = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected successfully");
}

void loop()
{
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0)
    {
        String payload = http.getString();
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject &json_parsed = jsonBuffer.parseObject(payload);

        if (!json_parsed.success())
        {
            Serial.println("parsing failed");
            delay(500);
            return;
        }
        String direction = json_parsed["direction"];
        Serial.println(direction);
    }
    else
    {
        Serial.println(httpCode);
    }
    delay(500);
};