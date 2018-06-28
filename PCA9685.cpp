#include "PCA9685.h"

PCA9685::PCA9685()
{
    _addr = PCA9685_DEFAULT_I2C_ADDR;
}

void PCA9685::init(uint8_t addr)
{
    _addr = addr;
    reset();
    setFrequency(1000);
}

void PCA9685::reset()
{
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, PCA9685_RESTART_BIT);
    delay(10);
}

void PCA9685::setFrequency(uint16_t freq)
{
    if (freq < 24) freq = 24;
    else if (freq > 1526) freq = 1526;
    float prescaleval = (25000000.0/4096.0)/freq - 1;

    uint8_t pre_scale = floor(prescaleval + 0.5);

    I2Cdev::readByte(_addr, PCA9685_MODE1_REG, _buffer);
    uint8_t oldmode = _buffer[0];
    uint8_t newmode = (oldmode&0x7F) | PCA9685_SLEEP_BIT; // set to sleep first
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, newmode); 
    I2Cdev::writeByte(_addr, PCA9685_PRESCALE, pre_scale);   // set the prescaler
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, oldmode);
    delay(5);
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, oldmode| 0xa0);   //  This sets the MODE1 register to turn on auto increment.
}

void PCA9685::setPwm(uint8_t pin, uint16_t led_on, uint16_t led_off)
{
    // map 1-16 to 0-15
    if (pin < 1) pin = 1;
    else if (pin > 16) pin=16;
    pin = pin - 1;

    uint8_t buffer[4];
   
    buffer[0] = led_on;
    buffer[1] = led_on >> 8;
    buffer[2] = led_off;
    buffer[3] = led_off >> 8;

    I2Cdev::writeBytes(_addr, PCA9685_LED0_ON_L+4*pin, 4, buffer);
}


ServoDriver::ServoDriver()
{
    _addr = PCA9685_DEFAULT_I2C_ADDR;
}


void ServoDriver::init(uint8_t addr)
{
    _addr = addr;
    reset();
    // default pulse range of servo: 0.5ms~2.5ms
    setServoPulseRange(500,2500);
    // default servo working frequency: 50Hz/20ms
    setFrequency(50);
}

void ServoDriver::setServoPulseRange(uint16_t min_pulse_width, uint16_t max_pulse_width, uint16_t max_servo_degree)
{
    float min, max;
    min = (2.46 * min_pulse_width)/10.0 - 1;
    max = (2.46 * max_pulse_width)/10.0 - 1;
    _min_pulse_width = min;
    _max_pulse_width = max;
    _max_servo_degree = max_servo_degree;
}

void ServoDriver::setAngle(uint8_t pin, uint16_t angle)
{
    if (angle > _max_servo_degree) angle = _max_servo_degree;
    setPwm(pin, 0, angle*((_max_pulse_width-_min_pulse_width)/_max_servo_degree)+_min_pulse_width);
}