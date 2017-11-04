#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <stdio.h>
#include <string.h>

#define pin_led 2

ESP8266WebServer server;

char *ssid = "XuanDuc";
char *passwd = "05061992";

void setup()
{
    pinMode(pin_led, OUTPUT);
    WiFi.begin(ssid, passwd);
    Serial.begin(115200);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.print("IP adress: ");
    Serial.print(WiFi.localIP());

    server.on("/", []() { server.send(200, "text/plain", "Hello world"); });
    server.on("/toggle", toggleLED);
    server.on("/params", queryString);
    server.begin();
}

void loop()
{
    server.handleClient();
}

void toggleLED()
{
    digitalWrite(pin_led, !digitalRead(pin_led));
    int status = digitalRead(pin_led);
    String statusStr;
    if (status)
    {
        //strcmp(statusStr, "HIGH");
        statusStr = "HIGH";
    }
    else
    {
        //strcmp(statusStr, "LOW");
        statusStr = "LOW";
    }
    server.send(200, "text/plain", "The light is turn " + statusStr);
}

void queryString()
{
    String name = server.arg("name");
    String age = server.arg("age");

    server.send(200, "text/plain", name + " " + age);
}