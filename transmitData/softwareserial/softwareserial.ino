#include "EmonLib.h"
// Include Emon Library
#include "WiFiClient.h"
#include "PubSubClient.h"
#include "ArduinoJson.h"

unsigned long current_time;
unsigned long previous;

struct Power
{
    double kwh;
    String id;
};

Power power;

// Create an instance
void setup()
{
    Serial.begin(115200);
    Serial.println("start calculate");
    
    current_time = millis();
    previous = 0;
}

void loop()
{
    current_time = millis();
    if (current_time - previous > 3000)
    {
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject &json_value = jsonBuffer.createObject();
        json_value["power"] = 20;
        json_value["arudino_id"] = "id20";
        char msg[200];
        json_value.printTo(msg, sizeof(msg));
        previous = current_time;

        Serial.println(msg);
    }
}
