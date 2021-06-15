#include <Arduino.h>
#include <SoftwareSerial.h>

const byte START = 128;
const byte FULL = 132;
const byte STOP = 173;
const byte DRIVE_PWM = 146;
const byte SENSORS = 142;
const byte BUMPS_AND_WHEELS_ID = 7;
const byte LIGHT_BUMPER_ID = 45;
const byte BUTTONS_ID = 18;

const int rxPin = 10;
const int txPin = 11;
const int speed = 96;

SoftwareSerial Roomba(rxPin,txPin);

void drivePwm(int leftPwm, int rightPwm) {
    Roomba.write(DRIVE_PWM);
    Roomba.write(highByte(leftPwm));
    Roomba.write(lowByte(leftPwm));
    Roomba.write(highByte(rightPwm));
    Roomba.write(lowByte(rightPwm));
}

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

    Serial.println("bumps and wheels: " + (String)readSensor(BUMPS_AND_WHEELS_ID));
    Serial.println("setup completed!");
}

void loop() {
    // write your code here
    if (readSensor(BUTTONS_ID) == 1) {
        drivePwm(0, 0);
        Roomba.write(STOP);
    }

    byte light = readSensor(LIGHT_BUMPER_ID);
    if (light > 0) {
        Serial.println("roomba light: " + (String)light);

        if (random(2)) {
            Serial.println("rotate left");
            drivePwm(speed, -speed);
        } else {
            Serial.println("rotate right");
            drivePwm(-speed, speed);
        }
        delay(2000);
        Serial.println("driving...");
        drivePwm(speed, speed);
    }
    delay(500);
}
