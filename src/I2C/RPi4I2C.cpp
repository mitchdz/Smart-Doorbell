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

#include "RPi4I2C.h"
#include "RPi4.h"

void RPi4I2C::init()
{
	this->timerDriver.init();
	this->gpioDriver.init();
	this->gpioDriver.pinMode(SDA, GPIO_OUTPUT);
	this->gpioDriver.pinMode(SCL, GPIO_OUTPUT);
	this->SDA_HIGH();
	this->SCL_HIGH();
}

void RPi4I2C::start()
{
	this->SDA_HIGH();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_HIGH();
	this->timerDriver.delay_us(pauseTime);
	this->SDA_LOW();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_LOW();
	this->timerDriver.delay_us(pauseTime);
}

void RPi4I2C::stop()
{
	this->SDA_LOW();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_HIGH();
	this->timerDriver.delay_us(pauseTime);
	this->SDA_HIGH();
	this->timerDriver.delay_us(pauseTime);
}

void RPi4I2C::sendNACK()
{
	this->SDA_HIGH();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_HIGH();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_LOW();
	this->timerDriver.delay_us(pauseTime);
	this->SDA_LOW();
	this->timerDriver.delay_us(pauseTime);
}

void RPi4I2C::sendACK()
{
	this->SDA_LOW();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_LOW();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_HIGH();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_LOW();
	this->timerDriver.delay_us(pauseTime);
	this->SDA_LOW();
	this->timerDriver.delay_us(pauseTime);
}

unsigned char RPi4I2C::write(unsigned char data)
{
	unsigned char ack;

	for(unsigned char i = 0; i < 8; i++)
	{
		if((data << i) & 0x80)
			this->SDA_HIGH();
		else
			this->SDA_LOW();

		this->timerDriver.delay_us(pauseTime);
		this->SCL_HIGH();
		this->timerDriver.delay_us(pauseTime);
		this->SCL_LOW();
	}

	this->SET_MODE_INPUT();
	this->timerDriver.delay_us(pauseTime);
	this->SCL_HIGH();
	this->timerDriver.delay_us(pauseTime);

	ack = (this->GET_STATE()) ? 0 : 1;

	this->SCL_LOW();
	this->timerDriver.delay_us(pauseTime);
	this->SET_MODE_OUTPUT();

	return ack;
}

unsigned char RPi4I2C::read()
{
	unsigned char data = 0;
	this->SET_MODE_INPUT();
	for(unsigned char i = 0; i < 8; i++)
	{
		this->timerDriver.delay_us(pauseTime);
		this->SCL_HIGH();
		this->timerDriver.delay_us(pauseTime);
		data = data << 1;

		if(this->GET_STATE()) data |= 1;

		this->SCL_LOW();
		this->timerDriver.delay_us(pauseTime);
	}

	this->SET_MODE_OUTPUT();
	return data;
}