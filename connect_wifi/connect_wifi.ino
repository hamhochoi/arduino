#include <ESP8266WiFi.h>

const char *ssid =  "ThuyHuong";     // replace with your wifi ssid and wpa2 key
const char *pass =  "09061994";

WiFiClient client;

//unsigned long time = 0;
 
void setup() 
{
       Serial.begin(9600);
       delay(10);
               
       Serial.println("Connecting to ");
       Serial.println(ssid); 
 
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 
      pinMode(LED_BUILTIN, OUTPUT);
      digitalWrite(LED_BUILTIN, LOW);
}
 
void loop() 
{      
      if(Serial.available() > 0){
        digitalWrite(LED_BUILTIN, HIGH);
        while(Serial.available()){
          Serial.read();
          //delay(3);
        }
        Serial.println("da nhan duoc du lieu");
      }
      //delay(10000);
      digitalWrite(LED_BUILTIN, LOW);
}

