const int LED = 13;
int brightness = 0;
int fade = 1;

void setup() {
 pinMode(LED, OUTPUT); 
}

void loop() {
    analogWrite(LED, brightness);
    brightness = brightness + fade;  
    if (brightness >= 255 || brightness <=0) {
      fade = -fade;  
    }
    delay(200);
 
}

