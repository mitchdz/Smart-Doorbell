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
 * RPi4GPIO
 *
 * This module acts as a driver for Raspberry Pi 4 GPIO pins
 */

#include "RPi4GPIO.h"
#include "RPi4.h"

void RPi4GPIO::noInterrupts()
{
	// save current interrupts
	irq1	 = IRQ_ENABLE1;
	irq2	 = IRQ_ENABLE2;
	irqbasic = IRQ_ENABLE_BASIC;

	// disable interrupts
	IRQ_DISABLE1	  = irq1;
	IRQ_DISABLE2	  = irq2;
	IRQ_DISABLE_BASIC = irqbasic;
}

void RPi4GPIO::interrupts()
{
	if(IRQ_ENABLE1 == 0)
	{
		IRQ_ENABLE1		 = irq1;
		IRQ_ENABLE2		 = irq2;
		IRQ_ENABLE_BASIC = irqbasic;
	}
}

void RPi4GPIO::pinMode(PIN pin, unsigned int mode)
{
	int reg	   = pin / 10;
	int offset = (pin % 10) * 3;
	GPFSEL[reg] &= ~((0b111 & ~mode) << offset);
	GPFSEL[reg] |= ((0b111 & mode) << offset);
}

void RPi4GPIO::digitalWrite(PIN pin, int val)
{
	int reg	   = pin / 32;
	int offset = pin % 32;

	if(val)
		GPSET[reg] = 1 << offset;
	else
		GPCLR[reg] = 1 << offset;
}

int RPi4GPIO::digitalRead(PIN pin)
{
	int reg	   = pin / 32;
	int offset = pin % 32;

	return (GPLEV[reg] >> offset) & 0x00000001;
}