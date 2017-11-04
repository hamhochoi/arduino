#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "ArduinoJson.h"
#include "SoftwareSerial.h"
#include "PubSubClient.h"
#include "WiFiClient.h"

char *ssid = "FTI";
char *passwd = "8888888888";

// char *ssid = "XuanDuc";
// char *passwd = "05061992";

WiFiClient esp8266Client;
PubSubClient client(esp8266Client);

long lastMsg = 0;
char *mqtt_server = "10.3.13.244";
// char *mqtt_server = "192.168.0.106";

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            //Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(50);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    };
    WiFi.begin(ssid, passwd);
    int wifi_ctr = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected successfully");
    client.setServer(mqtt_server, 1883);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    // int t = rand() % 20;
    // int h = 21 + rand() % 20;
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &json_weather = jsonBuffer.createObject();
    // json_weather["temperature"] = t;
    // json_weather["humidity"] = h;
    char msg[200];

    int av = Serial.available();

    if (av > 0)
    {
        String c;
        for (int i = 0; i < av; i++)
        {
            c = Serial.readStringUntil('\n');
        }

        int value = c.toInt();

        json_weather["temperature"] = value;
        json_weather.printTo(msg, sizeof(msg));
        client.publish("outTopic", msg);
    }

};
