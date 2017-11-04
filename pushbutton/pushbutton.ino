const int LED = 13;
const int BUTTON = 2;

int state = 0;
int val = LOW;
int old_val = 0;

void setup() {
   pinMode(LED, OUTPUT);
   pinMode(BUTTON, INPUT);
   Serial.begin(115200);
 
 }

 void loop() {
  val = digitalRead(BUTTON);
  
  if (val == HIGH) {
      Serial.println("Val is high");
      digitalWrite(LED, HIGH);
     
    } else {
      Serial.println("Val is low");
      digitalWrite(LED, LOW);
     
      }
}

//void loop() {
//    val = digitalRead(BUTTON);
//    if ((val == HIGH) && (old_val == LOW)) {
//        state = 1 - state;
//        delay(10);
//       
//      }
//      old_val = val;
//
//      if (state == 1) {
//          digitalWrite(LED, HIGH);
//        } else {
//          digitalWrite(LED, LOW);
//          }
//  }
