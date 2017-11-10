#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "ArduinoJson.h"

char *ssid = "FTI";
char *passwd = "8888888888";

String mac;

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

    mac = WiFi.macAddress();
}

void loop()
{
    int av = Serial.available();
    if (av > 0)
    {
        String c = Serial.readStringUntil('\n');
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& json_value = jsonBuffer.parseObject(c);
        if(!json_value.success()) {
            Serial.println("parse failed!!!");
        } else {
            Serial.println("parse done");
            json_value["mac"] = mac;
            char msg[200];
            json_value.printTo(msg, sizeof(msg));
            Serial.println(msg);
        }
    }
};