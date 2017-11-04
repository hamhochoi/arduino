#include "SoftwareSerial.h"

int E1 = 6; // speed
int M1 = 7; // direction
int E2 = 5; // speed
int M2 = 4; // direction
SoftwareSerial esp8266Serial(10, 12);

void setup()
{
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);
    Serial.begin(115200);
    while (!Serial)
    {
    }
    esp8266Serial.begin(115200);
}

void loop()
{
    String command = "";
    while (esp8266Serial.available())
    {
        delay(100);
        command = esp8266Serial.readStringUntil('\n');
        //Serial.println(command);
        moveRobot(command);
    }
}

void moveRobot(String command)
{
    Serial.println(command);
    command.trim();
    //Serial.println(command.length());

    if (command == "left")
    {
        digitalWrite(M1, HIGH);
        digitalWrite(M2, LOW);
        analogWrite(E1, 150);
        analogWrite(E2, 0);
    }

    else if (command == "right")
    {
        digitalWrite(M1, LOW);
        digitalWrite(M2, HIGH);
        analogWrite(E1, 0);
        analogWrite(E2, 150);
    }

    else if (command == "toward")
    {
        digitalWrite(M1, HIGH);
        digitalWrite(M2, HIGH);
        analogWrite(E1, 150);
        analogWrite(E2, 150);
    }
    else if (command == "backward")
    {
        digitalWrite(M1, LOW);
        digitalWrite(M2, LOW);
        analogWrite(E1, 150);
        analogWrite(E2, 150);
    }
    else if (command == "stop")
    {
        digitalWrite(M1, HIGH);
        digitalWrite(M2, HIGH);
        analogWrite(E1, 0);
        analogWrite(E2, 0);
    }
    else
    {
        Serial.println("not call");
    }
}
