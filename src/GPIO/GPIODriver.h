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
 * GPIODriver
 * 
 * This module acts as a parent class for drivers that control GPIO signals on
 * specific boards.
 */

#ifndef GPIODRIVER_H
#define GPIODRIVER_H

enum GPIO_SETUP
{
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
    GPIO_ALT0 = 4,
    GPIO_ALT1 = 5,
    GPIO_ALT2 = 6,
    GPIO_ALT3 = 7,
    GPIO_ALT4 = 3,
    GPIO_ALT5 = 2
};

enum GPIO_LEVEL
{
    GPIO_LOW = 0,
    GPIO_HIGH
};

typedef int PIN;

class GPIODriver
{
public:
    virtual void pioInit();
    virtual void noInterrupts();
    virtual void interrupts();
    virtual void pinMode(PIN pin, unsigned int mode);
    virtual void digitalWrite(PIN pin, int val);
    virtual int digitalRead(PIN pin);

    void pinsMode(PIN pins[], unsigned int numPins, int mode);
    void digitalWrites(PIN pins[], unsigned int numPins, int val);
    int digitalReads(PIN pins[], unsigned int numPins);

    virtual void delay_us(unsigned int micros);
    virtual void delay_ms(unsigned int millis);
};

#endif