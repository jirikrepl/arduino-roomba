#include <Arduino.h>
#include <SoftwareSerial.h>

int rxPin=10;
int txPin=11;
SoftwareSerial Roomba(rxPin,txPin);

void setup() {
    // write your initialization code here
    Roomba.begin(115200);
    Serial.begin(9600);

    Roomba.write(128);  //Start
    Roomba.write(132);  //Full mode
    delay(100);

    Roomba.write(142);
    Roomba.write(7);

    while (!Roomba.available());
    byte MSB = Roomba.read();
    byte LSB = Roomba.read();
    int returnVal = (MSB << 7) | LSB;
    Serial.println("roomba returned: " + (String)returnVal);

//    Roomba.write(135);  //Clean
//    delay(500);
//    Roomba.write(135);  //Clean

    Roomba.write(173);  //Stop
    Serial.println("setup completed!");
}

void loop() {
    // write your code here
}
