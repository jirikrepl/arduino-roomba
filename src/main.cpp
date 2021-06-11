#include <Arduino.h>
#include <SoftwareSerial.h>

const int START = 128;
const int FULL = 132;
const int STOP = 173;
const int SENSORS = 142;
const int BUMPS_AND_WHEELS = 7;

const int rxPin=10;
const int txPin=11;

SoftwareSerial Roomba(rxPin,txPin);

byte readSensor(int packetId) {
    Roomba.write(SENSORS);
    Roomba.write(packetId);

    while (!Roomba.available());
    return Roomba.read();
}

void setup() {
    // write your initialization code here
    Roomba.begin(115200);
    Serial.begin(9600);

    Roomba.write(START);
    Roomba.write(FULL);
    delay(100);

    Serial.println("roomba returned: " + (String)readSensor(BUMPS_AND_WHEELS));

    Roomba.write(STOP);
    Serial.println("setup completed!");
}

void loop() {
    // write your code here
}
