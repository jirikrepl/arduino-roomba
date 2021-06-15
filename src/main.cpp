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

const byte CLEAN_BUTTON_FLAG = 1;
const byte WHEEL_DROP_BOTH_FLAG = 12;
const byte BUMP_LEFT_FLAG = 2;
const byte BUMP_RIGHT_FLAG = 1;
const byte BUMP_BOTH_FLAG = 3;

const int rxPin = 10;
const int txPin = 11;
const int drive_speed = 96;

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
    Serial.println("setup completed!");
}

void loop() {
    // write your code here
    if (readSensor(BUTTONS_ID) == CLEAN_BUTTON_FLAG || readSensor(BUMPS_AND_WHEELS_ID) == WHEEL_DROP_BOTH_FLAG) {
        drivePwm(0, 0);
        Roomba.write(STOP);
        Serial.println("roomba stop!");
    }

    byte light = readSensor(LIGHT_BUMPER_ID);
    byte bump = readSensor(BUMPS_AND_WHEELS_ID);
    if (light > 0 || bump == BUMP_LEFT_FLAG || bump == BUMP_RIGHT_FLAG || bump == BUMP_BOTH_FLAG) {
        Serial.println("roomba light: " + (String)light + " bump: " + (String)bump);

        if (random(2)) {
            Serial.println("rotate left");
            drivePwm(drive_speed, -drive_speed);
        } else {
            Serial.println("rotate right");
            drivePwm(-drive_speed, drive_speed);
        }
        delay(2000);
        Serial.println("driving...");
        drivePwm(drive_speed, drive_speed);
    }
//    delay(500);
}
