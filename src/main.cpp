#include <Arduino.h>
#include <SoftwareSerial.h>

void setup() {
    // write your initialization code here
    int rxPin=10;
    int txPin=11;
    SoftwareSerial Roomba(rxPin,txPin);
    Roomba.begin(115200);

    Roomba.write(128);  //Start
    Roomba.write(132);  //Full mode
    delay(1000);

    Roomba.write(135);  //Clean
    delay(1000);
    Roomba.write(135);  //Clean

    Roomba.write(173);  //Stop
}

void loop() {
    // write your code here
}
