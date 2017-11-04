char val;
int ledpin = 8;

void setup()
{
    pinMode(ledpin, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    if (Serial.available())
    {
        val = Serial.read();
    }

    if (val == 'H')
    {
        digitalWrite(ledpin, HIGH);
    }
    else
    {
        digitalWrite(ledpin, LOW);
    }
    delay(100);
}