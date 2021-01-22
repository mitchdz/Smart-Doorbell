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

#ifndef RPI4GPIO_H
#define RPI4GPIO_H

#include "GPIODriver.h"

class RPi4GPIO : GPIODriver
{
private:
    volatile unsigned int *gpio;
    int irq1 = 0;
    int irq2 = 0;
    int irqbasic = 0;

public:
    void init();
    void noInterrupts();
    void interrupts();
    void pinMode(PIN pin, unsigned int mode);
    void digitalWrite(PIN pin, int val);
    int digitalRead(PIN pin);
};

#endif