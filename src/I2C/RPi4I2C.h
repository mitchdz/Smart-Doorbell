/*
 * MIT License
 *
 * Copyright (c) 2021 Lena Voytek
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * RPI4I2C
 *
 * This module is an I2C protocol driver for the Raspberry Pi 4
 */

#ifndef RPI4I2C_H
#define RPI4I2C_H

#include "I2CDriver.h"
#include "RPi4GPIO.h"
#include "RPi4Timer.h"

enum I2CWire
{
	SDA = 2,
	SCL = 3
};

class RPi4I2C : public I2CDriver
{
  private:
	const unsigned int pauseTime = 30;
	RPi4GPIO		   gpioDriver;
	RPi4Timer		   timerDriver;

	void SCL_HIGH();
	void SCL_LOW();
	void SDA_HIGH();
	void SDA_LOW();

	void SET_MODE_INPUT();
	void SET_MODE_OUTPUT();

	int GET_STATE();

  public:
	void		  init();
	void		  start();
	void		  stop();
	void		  sendNACK();
	void		  sendACK();
	unsigned char write(unsigned char data);
	unsigned char read();
};

inline void RPi4I2C::SCL_HIGH() { this->gpioDriver.digitalWrite(SCL, GPIO_HIGH); }
inline void RPi4I2C::SCL_LOW() { this->gpioDriver.digitalWrite(SCL, GPIO_LOW); }
inline void RPi4I2C::SDA_HIGH() { this->gpioDriver.digitalWrite(SDA, GPIO_HIGH); }
inline void RPi4I2C::SDA_LOW() { this->gpioDriver.digitalWrite(SDA, GPIO_LOW); }
inline void RPi4I2C::SET_MODE_INPUT() { this->gpioDriver.pinMode(SDA, GPIO_INPUT); }
inline void RPi4I2C::SET_MODE_OUTPUT() { this->gpioDriver.pinMode(SDA, GPIO_OUTPUT); }
inline int	RPi4I2C::GET_STATE() { return this->gpioDriver.digitalRead(SDA); }
#endif