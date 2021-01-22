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
 * RPi4Timer
 *
 * This module acts as the driver for Raspberry Pi 4 timers
 */

#include <time.h>

#include "RPi4Timer.h"
#include "RPi4.h"

unsigned long get_microsecond_timestamp()
{
	struct timespec t;

	if(clock_gettime(CLOCK_MONOTONIC_RAW, &t) != 0) { return 0; }

	return (unsigned long) t.tv_sec * 1000000 + t.tv_nsec / 1000;
}

void RPi4Timer::delay_us(unsigned int micros)
{
	unsigned long nowtime = get_microsecond_timestamp();
	while((get_microsecond_timestamp() - nowtime) < micros / 2) {}
}