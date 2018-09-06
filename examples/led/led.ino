#include "PCA9685.h"
#include <Wire.h>

PCA9685 led;


void setup()
{
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Serial.begin(9600);
    led.init(0x7f);
    // Set freq to 100Hz, range from 24Hz~1526hz
    led.setFrequency(100);
}

void loop()
{
    // Drive 8 leds in turns
    for (int i = 1; i < 9; i++)
    {
        // For example, if I want to output 20% PWM(no delay time),
        // I need to set led_on=0 and led_off=20%*4096=819.
        led.setPwm(i, 0, 819);
        delay(1000);
        // output 0% PWM
        led.setPwm(i, 0, 0);
        delay(1000);
    }
}