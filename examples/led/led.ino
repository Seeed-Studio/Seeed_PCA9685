#include "PCA9685.h"
#include <Wire.h>

PCA9685 led;


void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Serial.begin(9600);
    led.init(0x7f);
    // Set freq to 100Hz, range from 24Hz~1526hz
    led.setFrequency(100);

    for (int i = 1; i < 17; i++) {
        led.setPwm(i, 0, 1024);
    }
}

void loop() {
}