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
 * RPI4SPI
 *
 * This module is an SPI protocol driver for the Raspberry Pi 4
 */

#include "RPi4SPI.h"
#include "RPi4.h"

void RPi4SPI::init(unsigned int frequency, int settings)
{
	this->gpioDriver.init();
	SPI0CSbits.TA = 0;
	this->gpioDriver.pinMode(9, GPIO_ALT0);
	this->gpioDriver.pinMode(10, GPIO_ALT0);
	this->gpioDriver.pinMode(11, GPIO_ALT0);

	SPI0CLK			 = 250000000 / frequency;
	SPI0CS			 = settings;
	SPI0CSbits.CLEAR = 3;
	SPI0CSbits.TA	 = 1;
}

char RPi4SPI::spiTransfer(char toSend)
{
	SPI0FIFO = toSend;
	while(!SPI0CSbits.DONE) {}
	return SPI0FIFO;
}

short RPi4SPI::spiTransfer16(short toSend)
{
	short rec;
	SPI0CSbits.TA = 1;
	rec			  = this->spiTransfer((toSend & 0xFF00) >> 8);	  // send data MSB first
	rec			  = (rec << 8) | this->spiTransfer(toSend & 0xFF);
	SPI0CSbits.TA = 0;	  // turn off SPI
	return rec;
}