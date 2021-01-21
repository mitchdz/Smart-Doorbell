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

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "RPi4Timer.h"
#include "RPi4.h"

#ifdef DEBUG
#include <stdio.h>
#endif

void RPi4Timer::init()
{
	int  mem_fd;
	void *reg_map;

	// /dev/mem is a psuedo-driver for accessing memory in the Linux filesystem
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
#ifdef DEBUG
		printf("can't open /dev/mem \n");
#endif
	}

    reg_map = mmap(
	  NULL,             //Address at which to start local mapping (null means don't-care)
      BLOCK_SIZE,       //Size of mapped memory block
      PROT_READ|PROT_WRITE,// Enable both reading and writing to the mapped memory
      MAP_SHARED,       // This program does not have exclusive access to this memory
      mem_fd,           // Map to /dev/mem
      SYS_TIMER_BASE);       // Offset to Timer peripheral

	if (reg_map == MAP_FAILED) {
#ifdef DEBUG
		printf("sys timer mmap error %d\n", (int)reg_map);
#endif
		close(mem_fd);
		return;
	}

	this->sys_timer = (volatile unsigned *)reg_map;

    reg_map = mmap(
	  NULL,             //Address at which to start local mapping (null means don't-care)
      BLOCK_SIZE,       //Size of mapped memory block
      PROT_READ|PROT_WRITE,// Enable both reading and writing to the mapped memory
      MAP_SHARED,       // This program does not have exclusive access to this memory
      mem_fd,           // Map to /dev/mem
      ARM_TIMER_BASE);       // Offset to interrupts

	if (reg_map == MAP_FAILED) {
#ifdef DEBUG
		printf("arm timer mmap error %d\n", (int)reg_map);
#endif
		close(mem_fd);
		return;
	}

	this->arm_timer = (volatile unsigned *)reg_map;
	close(mem_fd);
}

void RPi4Timer::delay_us(unsigned int micros)
{
	unsigned long nowtime = get_microsecond_timestamp();
	while((get_microsecond_timestamp() - nowtime)<micros/2);
}