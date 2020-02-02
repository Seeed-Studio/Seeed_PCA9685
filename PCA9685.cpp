#include "PCA9685.h"

PCA9685::PCA9685() {
    _addr = PCA9685_DEFAULT_I2C_ADDR;
}

void PCA9685::init(uint8_t addr) {
    _addr = addr;
    restart();
    setFrequency(1000);     // set default frequency
}

void PCA9685::restart() {
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, PCA9685_RESTART_BIT);
    delay(10);

    // Set to sleep first, to turn off internal oscillator
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, PCA9685_SLEEP_BIT);
    delay(2);

    // Write logic 1 to both SLEEP bit and EXTCLK bit, the switch is now made. Enable the external oscillator
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, PCA9685_EXTCLK_BIT | PCA9685_SLEEP_BIT);

    // Turn on oscillator now
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, 0x00);
    delay(2);

    // // restart again
    // I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, PCA9685_RESTART_BIT);
}

void PCA9685::setFrequency(uint16_t freq) {
    if (freq < 24) {
        freq = 24;
    } else if (freq > 1526) {
        freq = 1526;
    }
    float prescaleval = (25000000.0 / 4096.0) / freq - 1;

    uint8_t pre_scale = floor(prescaleval + 0.5);

    I2Cdev::readByte(_addr, PCA9685_MODE1_REG, _buffer);
    // Serial.print("oldmode = ");
    // Serial.println(_buffer[0], BIN);

    // PRE_SCALE can only be set when SLEEP is logic 1
    // go to sleep
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, (_buffer[0] & 0x7F) | 0x10);
    delay(2);
    I2Cdev::writeByte(_addr, PCA9685_PRESCALE, pre_scale);
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, _buffer[0]);
    delay(2);
    I2Cdev::writeByte(_addr, PCA9685_MODE1_REG, _buffer[0] | 0xa0);
    delay(2);
}

void PCA9685::setPwm(uint8_t pin, uint16_t led_on, uint16_t led_off) {
    // map 1-16 to 0-15
    if (pin < 1) {
        pin = 1;
    } else if (pin > 16) {
        pin = 16;
    }
    pin = pin - 1;

    uint8_t buffer[4];

    buffer[0] = led_on;
    buffer[1] = led_on >> 8;
    buffer[2] = led_off;
    buffer[3] = led_off >> 8;

    I2Cdev::writeBytes(_addr, PCA9685_LED0_ON_L + 4 * pin, 4, buffer);
}


ServoDriver::ServoDriver() {
    _addr = PCA9685_DEFAULT_I2C_ADDR;
}


void ServoDriver::init(uint8_t addr) {
    _addr = addr;
    restart();
    // default pulse range of servo: 0.5ms~2.5ms
    setServoPulseRange(500, 2500);
    // default servo working frequency: 50Hz/20ms
    setFrequency(50);
}

void ServoDriver::setServoPulseRange(uint16_t min_pulse_width, uint16_t max_pulse_width, uint16_t max_servo_degree) {
    float min, max;
    min = (2.46 * min_pulse_width) / 10.0 - 1;
    max = (2.46 * max_pulse_width) / 10.0 - 1;
    _min_pulse_width = min;
    _max_pulse_width = max;
    _max_servo_degree = max_servo_degree;
}

void ServoDriver::setAngle(uint8_t pin, uint16_t angle) {
    if (angle > _max_servo_degree) {
        angle = _max_servo_degree;
    }
    setPwm(pin, 0, angle * ((_max_pulse_width - _min_pulse_width) / _max_servo_degree) + _min_pulse_width);
}