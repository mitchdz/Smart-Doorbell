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
 * I2CDriver
 *
 * This module acts as a parent class for drivers that control the I2C protocol on
 * specific boards
 */

#include <stdlib.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#include "Debug.h"

#include "I2CDriver.h"

char i2c_filename[20];
FILE i2c_file;

/**
 * Initialize I2C bus of given number for transactions with a slave device with a given address
 * @param i2c_bus The I2C bus number
 * @param address The slave device address
 */
void I2C_init(int i2c_bus, unsigned char address)
{
	snprintf(i2c_filename, 19, "/dev/i2c-%d", i2c_bus);
	i2c_file = open(i2c_filename, O_RDWR);

	if(i2c_file < 0)
	{
		ERROR_PRINTLN("%19s does not exist.", i2c_filename);
		return;
	}

	if(ioctl(i2c_file, I2C_SLAVE, address) < 0)
	{
		ERROR_PRINTLN("Cannot change I2C slave address.");
	}
}