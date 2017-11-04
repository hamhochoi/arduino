
void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
}

void loop()
{
    int n = rand() % 20 + 20 ;
    Serial.println(n);
    delay(2000);
}