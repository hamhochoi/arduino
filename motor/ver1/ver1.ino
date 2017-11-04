int E1 = 6; // speed
int M1 = 7; // direction
int E2 = 5; // speed
int M2 = 4; // direction

void setup() {
  pinMode(M1, OUTPUT);  
  pinMode(M2, OUTPUT);  
}

void loop() {
  int value;
//  for(value = 0; value <= 255; value += 1) {
    digitalWrite(M1, HIGH);  
    digitalWrite(M2, LOW);
    analogWrite(E1, 150);
    analogWrite(E2, 150);

    delay(30);
//  }  
}
