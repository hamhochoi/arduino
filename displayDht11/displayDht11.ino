#include <DHT.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    Serial.println("Fail to read from DHT");  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fail to read");
    lcd.setCursor(0, 1);
    lcd.print("from DHT");
  } else {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Humidity: ");
     lcd.setCursor(10, 0);
     lcd.print(h);
     lcd.print("%");
     lcd.setCursor(0, 1);
     lcd.print("Temp: ");
     lcd.setCursor(10, 1);
     lcd.print(t);
     lcd.print("*C");
  }
  delay(5000);
}
