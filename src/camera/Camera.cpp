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
 * Camera
 * 
 * This module controls the setup and intake of live video from the ArduCam 5MP
 * Plus OV5642 Camera
 */

#include "Camera.h"
#include "ov5642_regs.h"

Camera::Camera(unsigned int cs)
{
	this->csPin = cs;
	this->format = IMG_JPEG;
}

void Camera::init()
{
	this->wrSensorReg16_8(0x3008, 0x80);
	this->wrSensorRegs16_8(OV5642_QVGA_Preview);

	if (this->format == IMG_JPEG)
	{
		this->wrSensorRegs16_8(OV5642_JPEG_Capture_QSXGA);
		this->wrSensorRegs16_8(ov5642_320x240);
		this->wrSensorReg16_8(0x3818, 0xa8);
		this->wrSensorReg16_8(0x3621, 0x10);
		this->wrSensorReg16_8(0x3801, 0xb0);
		this->wrSensorReg16_8(0x4407, 0x04);			
	}
	else
	{
		unsigned char reg_val;
		this->wrSensorReg16_8(0x4740, 0x21);
		this->wrSensorReg16_8(0x501e, 0x2a);
		this->wrSensorReg16_8(0x5002, 0xf8);
		this->wrSensorReg16_8(0x501f, 0x01);
		this->wrSensorReg16_8(0x4300, 0x61);
		this->rdSensorReg16_8(0x3818, &reg_val);
		this->wrSensorReg16_8(0x3818, (reg_val | 0x60) & 0xff);
		this->rdSensorReg16_8(0x3621, &reg_val);
		this->wrSensorReg16_8(0x3621, reg_val & 0xdf);
	}

	this->setResolution(RES_320x240);
}