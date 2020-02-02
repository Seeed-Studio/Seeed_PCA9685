#include "PCA9685.h"
#include <Wire.h>

ServoDriver servo;


void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Serial.begin(9600);
    servo.init(0x7f);
    // uncomment this line if you need to use a special servo
    // servo.setServoPulseRange(600,2400,180);
}

void loop() {
    // Drive 8 servos in turns
    for (int i = 1; i < 9; i++) {
        servo.setAngle(i, 0);
        delay(1000);
        servo.setAngle(i, 90);
        delay(1000);
    }
}