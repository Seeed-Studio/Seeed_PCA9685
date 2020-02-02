/*
    PCA9685.h
    A library for the Grove - 16-Channel Servo Driver(PCA9685)

    Copyright (c) 2018 seeed technology co., ltd.
    Website    : www.seeed.cc
    Author     : Jerry Yip
    Create Time: 2018-06
    Version    : 0.2
    Change Log :
                v0.1 Init.
                v0.2 Use external oscillator to improve accuracy of PWM frequency.

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef __PCA9685_H__
#define __PCA9685_H__

#include "I2Cdev.h"

#define PCA9685_DEFAULT_I2C_ADDR    0x7f

#define PCA9685_MODE1_REG       0x00
#define PCA9685_MODE2_REG       0x01
#define PCA9685_LED0_ON_L       0x06
#define PCA9685_ALL_LED_ON_L    0xfa
#define PCA9685_PRESCALE        0xfe

#define PCA9685_SLEEP_BIT       0x10
#define PCA9685_EXTCLK_BIT      0x40
#define PCA9685_RESTART_BIT     0x80

class PCA9685 {
  public:
    PCA9685();

    /*************************************************************
        Description
         Initialize PCA9685
        Parameter
         addr: I2C address of PCA9685, based on the hardware address pin,
               range from  0x40 to 0x7f (except 0x70h), default address is 0x7f
        Return
         Null.
    *************************************************************/
    void init(uint8_t addr = PCA9685_DEFAULT_I2C_ADDR);

    /*************************************************************
        Description
         Restart PCA9685
        Parameter
         Null.
        Return
         Null.
    *************************************************************/
    void restart();

    /*************************************************************
        Description
         Set PWM output frequency
        Parameter
         freq: range from 24Hz~1526Hz
        Return
         Null.
    *************************************************************/
    void setFrequency(uint16_t freq);

    // led_on & led_off : 0~4096
    /*************************************************************
        Description
         Set the PWM
        Parameter
         pin: the selected PWM pin to control, range from 1-16.
         led_on: the ON time stamp of pwm output, range from 0-4095.
                The duty cycle of PWM is 4096. When the counter equals
                to led_on time stamp, the output turns to High, and when
                the counter equals to led_off time stamp, the output
                turns to Low. For example, if I want to output 20% PWM(no delay time),
                I need to set led_on=0 and led_off=20%*4096=819.
         led_off: the OFF time stamp of pwm output, range from 0-4095
        Return
         Null.
    *************************************************************/
    void setPwm(uint8_t pin, uint16_t led_on, uint16_t led_off);


  protected:
    uint8_t _addr;
    uint8_t _buffer[16];
};

class ServoDriver : public PCA9685 {
  public:
    ServoDriver();

    /*************************************************************
        Description
         Initialize ServoDriver
        Parameter
         addr: I2C address of PCA9685, based on the hardware address pin,
               range from  0x40 to 0x7f (except 0x70h), default address is 0x7f
        Return
         Null.
    *************************************************************/
    void init(uint8_t addr = PCA9685_DEFAULT_I2C_ADDR);

    /*************************************************************
        Description
         Set the pulse range of a servo.
        Parameter
         min_pulse_width: the minimum pulse width of a servo. Generally it is 500us.
         max_pulse_width: the maximum pulse width of a servo. Generally it is 2500us.
         max_servo_degree: the operating travel of a servo. Generally it is 180 degree.
        Return
         Null.
    *************************************************************/
    void setServoPulseRange(uint16_t min_pulse_width, uint16_t max_pulse_width, uint16_t max_servo_degree = 180);


    /*************************************************************
        Description
         Set a angle to a servo.
        Parameter
         pin: the selected PWM pin to control, range from 1-16.
         angle: range from 0 to max_servo_degree(default to 180,
                see setServoPulseRange() to set it.)
        Return
         Null.
    *************************************************************/
    void setAngle(uint8_t pin, uint16_t angle);

  private:
    uint16_t _min_pulse_width, _max_pulse_width, _max_servo_degree;
};

#endif //  __PCA9685_H__