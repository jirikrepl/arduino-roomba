#include <Arduino.h>
#include <SoftwareSerial.h>

const byte START = 128;
const byte FULL = 132;
const byte STOP = 173;
const byte DRIVE_PWM = 146;
const byte SENSORS = 142;
const byte BUMPS_AND_WHEELS = 7;
const byte LIGHT_BUMPER = 45;

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

    const int rightPwm = 64;
    const int leftPwm = -64;
    Roomba.write(DRIVE_PWM);
    Roomba.write(highByte(rightPwm));
    Roomba.write(lowByte(rightPwm));
    Roomba.write(highByte(leftPwm));
    Roomba.write(lowByte(leftPwm));
    delay(1000);

    Serial.println("roomba returned: " + (String)readSensor(BUMPS_AND_WHEELS));

    Roomba.write(STOP);
    Serial.println("setup completed!");
}

void loop() {
    // write your code here
    byte bump = readSensor(LIGHT_BUMPER);
    if (bump > 0) {
        Serial.println("roomba bump: " + (String)bump);
    }
    delay(500);
}
