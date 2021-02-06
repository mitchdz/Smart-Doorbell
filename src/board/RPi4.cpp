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
 * RPi4
 *
 * Board-Specific definitions for the Raspberry Pi 4
 */

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "RPi4.h"

void RPi4Board::boardInit()
{
	int	   mem_fd;
	void * reg_map;

	// /dev/mem is a psuedo-driver for accessing memory in the Linux filesystem
	if((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
	{
#ifdef DEBUG
		printf("can't open /dev/mem \n");
#endif
		exit(-1);
	}

	reg_map =
		mmap(NULL,			// Address at which to start local mapping (null means don't-care)
			 BLOCK_SIZE,	// Size of mapped memory block
			 PROT_READ | PROT_WRITE,	// Enable both reading and writing to the mapped memory
			 MAP_SHARED,	// This program does not have exclusive access to this memory
			 mem_fd,		// Map to /dev/mem
			 GPIO_BASE);	// Offset to GPIO peripheral

	if(reg_map == MAP_FAILED)
	{
#ifdef DEBUG
		printf("gpio mmap error %d\n", (int) reg_map);
#endif
		close(mem_fd);
		exit(-1);
	}

	gpio = (volatile unsigned *) reg_map;

	reg_map =
		mmap(NULL,			// Address at which to start local mapping (null means don't-care)
			 BLOCK_SIZE,	// Size of mapped memory block
			 PROT_READ | PROT_WRITE,	// Enable both reading and writing to the mapped memory
			 MAP_SHARED,	// This program does not have exclusive access to this memory
			 mem_fd,		// Map to /dev/mem
			 SPI0_BASE);	// Offset to SPI peripheral

	if(reg_map == MAP_FAILED)
	{
#ifdef DEBUG
		printf("spi mmap error %d\n", (int) reg_map);
#endif
		close(mem_fd);
		exit(-1);
	}

	spi = (volatile unsigned *) reg_map;

	reg_map =
		mmap(NULL,			// Address at which to start local mapping (null means don't-care)
			 BLOCK_SIZE,	// Size of mapped memory block
			 PROT_READ | PROT_WRITE,	// Enable both reading and writing to the mapped memory
			 MAP_SHARED,	// This program does not have exclusive access to this memory
			 mem_fd,		// Map to /dev/mem
			 PWM_BASE);		// Offset to PWM peripheral

	if(reg_map == MAP_FAILED)
	{
#ifdef DEBUG
		printf("pwm mmap error %d\n", (int) reg_map);
#endif
		close(mem_fd);
		exit(-1);
	}

	pwm = (volatile unsigned *) reg_map;

	reg_map =
		mmap(NULL,			// Address at which to start local mapping (null means don't-care)
			 BLOCK_SIZE,	// Size of mapped memory block
			 PROT_READ | PROT_WRITE,	// Enable both reading and writing to the mapped memory
			 MAP_SHARED,		 // This program does not have exclusive access to this memory
			 mem_fd,			 // Map to /dev/mem
			 SYS_TIMER_BASE);	 // Offset to Timer peripheral

	if(reg_map == MAP_FAILED)
	{
#ifdef DEBUG
		printf("sys timer mmap error %d\n", (int) reg_map);
#endif
		close(mem_fd);
		exit(-1);
	}

	sys_timer = (volatile unsigned *) reg_map;

	reg_map =
		mmap(NULL,			// Address at which to start local mapping (null means don't-care)
			 BLOCK_SIZE,	// Size of mapped memory block
			 PROT_READ | PROT_WRITE,	// Enable both reading and writing to the mapped memory
			 MAP_SHARED,		 // This program does not have exclusive access to this memory
			 mem_fd,			 // Map to /dev/mem
			 ARM_TIMER_BASE);	 // Offset to interrupts

	if(reg_map == MAP_FAILED)
	{
#ifdef DEBUG
		printf("arm timer mmap error %d\n", (int) reg_map);
#endif
		close(mem_fd);
		exit(-1);
	}

	arm_timer = (volatile unsigned *) reg_map;

	reg_map =
		mmap(NULL,			// Address at which to start local mapping (null means don't-care)
			 BLOCK_SIZE,	// Size of mapped memory block
			 PROT_READ | PROT_WRITE,	// Enable both reading and writing to the mapped memory
			 MAP_SHARED,	// This program does not have exclusive access to this memory
			 mem_fd,		// Map to /dev/mem
			 UART_BASE);	// Offset to UART peripheral

	if(reg_map == MAP_FAILED)
	{
#ifdef DEBUG
		printf("uart mmap error %d\n", (int) reg_map);
#endif
		close(mem_fd);
		exit(-1);
	}

	uart = (volatile unsigned *) reg_map;

	reg_map =
		mmap(NULL,			// Address at which to start local mapping (null means don't-care)
			 BLOCK_SIZE,	// Size of mapped memory block
			 PROT_READ | PROT_WRITE,	// Enable both reading and writing to the mapped memory
			 MAP_SHARED,	  // This program does not have exclusive access to this memory
			 mem_fd,		  // Map to /dev/mem
			 CM_PWM_BASE);	  // Offset to ARM timer peripheral

	if(reg_map == MAP_FAILED)
	{
#ifdef DEBUG
		printf("cm_pwm mmap error %d\n", (int) reg_map);
#endif
		close(mem_fd);
		exit(-1);
	}

	cm_pwm = (volatile unsigned *) reg_map;
	close(mem_fd);
}