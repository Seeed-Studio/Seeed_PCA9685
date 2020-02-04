# Seeed PCA9685 Library  [![Build Status](https://travis-ci.com/Seeed-Studio/Seeed_PCA9685.svg?branch=master)](https://travis-ci.com/Seeed-Studio/Seeed_PCA9685)
---
This is the Arduino Library for Seeed's PCA9685 based products. For now, it's Grove - 16-Channel Servo Driver(PCA9685).


## Usage Tips
---
The PCA9685 is an I2C-bus controlled 16-channel LED controller. It can be used as RGB or RGBA LED Drivers, Servo Drivers, etc.

Please note that PCA9685 has a `ALL CALL I2C-bus address 0x70`, this address is for programming all the PCA9685s in the bus at the same time. This address is enabled by default and disabled after `PCA9685::init()` or `ServoDriver::init()`.


## Examples
---
### Servo
This example drives 8 servos in turns. The library provides a sub-class of `class PCA9685`, named `ServoDriver`. In that class, `ServoDriver::setAngle()` can be used to control a servo directly.

### Led
PCA9685 can also drive leds with PWM.


## Change I2C address
---
The default I2C address of Grove - 16-Channel Servo Driver(PCA9685) is 0x7f. If you need to change the I2C address, there are 6 hardware address pin on the back and they are default to **HIGH**. Cut the line between the right two pads and solder the left two pads together to set it to **LOW**.

![image](https://user-images.githubusercontent.com/18615354/42022774-b58f5c7c-7af0-11e8-8f73-acacfeb46198.png)

The following picture is the address table of PCA9685:

![image](https://user-images.githubusercontent.com/18615354/42022263-6e072926-7aef-11e8-8193-c27a6e64700b.png)

----

This software is written by Jerry Yip for seeed studio and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>


[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/grove-16channel-servo-driver-pca9685)](https://github.com/igrigorik/ga-beacon)

