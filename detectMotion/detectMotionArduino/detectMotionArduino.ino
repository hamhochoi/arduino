int Status = 12;  // Digital pin D6
int sensor = 13;  // Digital pin D7

int numberPerson = 0;
int i = 0;

void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT);   // declare sensor as input
  pinMode(Status, OUTPUT);  // declare LED as output
}

void loop() {

  long state = digitalRead(sensor);
    if(state == HIGH) {
      digitalWrite (Status, HIGH);
      Serial.println("Motion detected!");
      delay(1000);
    }
    else {
      digitalWrite (Status, LOW);
      Serial.println("Motion absent!");
      delay(1000);
      }
}


//void setup()
//{
//    pinMode(pinLed, OUTPUT);
//    pinMode(pirPin, INPUT);
//    digitalWrite(pinLed, LOW);
//    Serial.begin(115200);
//}

//void loop()
//{
//
//    long pirValue = digitalRead(pirPin);
//    if (pirValue == LOW)
//    {
//        digitalWrite(pinLed, LOW);
//        i = 0;
//        Serial.print("Not detected ");
//        Serial.println(i);
//        delay(500);
//    }
//    else if (pirValue == HIGH)
//    {
//        i += 1;
//        digitalWrite(pinLed, HIGH);
//        // Serial.print("Detect ");
//        // Serial.println(i);
//        if (i == 1)
//        {
//            numberPerson++;
//            Serial.print(numberPerson );
//            Serial.println(i);
//        }
//        delay(500);
//    }
//}

