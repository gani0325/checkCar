#include <string.h>

void setup()
{
    Serial.begin(9600);
}

void loop()
{

    //Serial.print("hi");  
    if(Serial.available()) {
        char data[8];
        char buf;
        
        for (int i = 0; i < 8; i++) {
            buf = Serial.read();
            //Serial.print("hi");
            data[i] = buf;
            
        }
        Serial.print(data);
    }

    delay(100);
}