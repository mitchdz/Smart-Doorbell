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
	this->csPin	 = cs;
	this->format = IMG_JPEG;
}

void Camera::init()
{
	this->wrSensorReg16_8(0x3008, 0x80);
	this->wrSensorRegs16_8(OV5642_QVGA_Preview);

	if(this->format == IMG_JPEG)
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

void Camera::activate() {}

void Camera::deactivate() {}

void Camera::setImageFormat(IMAGE_TYPE format) { this->format = format; }

void Camera::setResolution(RESOLUTION res)
{
	switch(res)
	{
		case RES_320x240:
			this->wrSensorRegs16_8(ov5642_320x240);
			break;
		case RES_640x480:
			this->wrSensorRegs16_8(ov5642_640x480);
			break;
		case RES_1024x768:
			this->wrSensorRegs16_8(ov5642_1024x768);
			break;
		case RES_1280x960:
			this->wrSensorRegs16_8(ov5642_1280x960);
			break;
		case RES_1600x1200:
			this->wrSensorRegs16_8(ov5642_1600x1200);
			break;
		case RES_2048x1536:
			this->wrSensorRegs16_8(ov5642_2048x1536);
			break;
		case RES_2592x1944:
			this->wrSensorRegs16_8(ov5642_2592x1944);
			break;
		default:
			break;
	}
}

void Camera::setColorSaturation(COLOR_SATURATION sat)
{
	this->wrSensorReg16_8(0x5001, 0xff);

	switch(sat)
	{
		case SAT_4:
			this->wrSensorReg16_8(0x5583, 0x80);
			this->wrSensorReg16_8(0x5584, 0x80);
			break;
		case SAT_3:
			this->wrSensorReg16_8(0x5583, 0x70);
			this->wrSensorReg16_8(0x5584, 0x70);
			break;
		case SAT_2:
			this->wrSensorReg16_8(0x5583, 0x60);
			this->wrSensorReg16_8(0x5584, 0x60);
			break;
		case SAT_1:
			this->wrSensorReg16_8(0x5583, 0x50);
			this->wrSensorReg16_8(0x5584, 0x50);
			break;
		case SAT_0:
			this->wrSensorReg16_8(0x5583, 0x40);
			this->wrSensorReg16_8(0x5584, 0x40);
			break;
		case SAT_NEG_1:
			this->wrSensorReg16_8(0x5583, 0x30);
			this->wrSensorReg16_8(0x5584, 0x30);
			break;
		case SAT_NEG_2:
			this->wrSensorReg16_8(0x5583, 0x20);
			this->wrSensorReg16_8(0x5584, 0x20);
			break;
		case SAT_NEG_3:
			this->wrSensorReg16_8(0x5583, 0x10);
			this->wrSensorReg16_8(0x5584, 0x10);
			break;
		case SAT_NEG_4:
			this->wrSensorReg16_8(0x5583, 0x00);
			this->wrSensorReg16_8(0x5584, 0x00);
			break;
		default:
			this->wrSensorReg16_8(0x5583, 0x40);
			this->wrSensorReg16_8(0x5584, 0x40);
			break;
	}

	this->wrSensorReg16_8(0x5580, 0x02);
}

void Camera::setBrightness(BRIGHTNESS level)
{
	this->wrSensorReg16_8(0x5001, 0xff);

	switch(level)
	{
		case BRIGHTNESS_4:
		case BRIGHTNESS_NEG_4:
			this->wrSensorReg16_8(0x5589, 0x40);
			break;
		case BRIGHTNESS_3:
		case BRIGHTNESS_NEG_3:
			this->wrSensorReg16_8(0x5589, 0x30);
			break;
		case BRIGHTNESS_2:
		case BRIGHTNESS_NEG_2:
			this->wrSensorReg16_8(0x5589, 0x20);
			break;
		case BRIGHTNESS_1:
		case BRIGHTNESS_NEG_1:
			this->wrSensorReg16_8(0x5589, 0x10);
			break;
		case BRIGHTNESS_0:
		default:
			this->wrSensorReg16_8(0x5589, 0x00);
			break;
	}

	this->wrSensorReg16_8(0x5580, 0x04);

	switch(level)
	{
		case BRIGHTNESS_NEG_4:
		case BRIGHTNESS_NEG_3:
		case BRIGHTNESS_NEG_2:
		case BRIGHTNESS_NEG_1:
			this->wrSensorReg16_8(0x558a, 0x08);
			break;

		case BRIGHTNESS_4:
		case BRIGHTNESS_3:
		case BRIGHTNESS_2:
		case BRIGHTNESS_1:
		case BRIGHTNESS_0:
		default:
			this->wrSensorReg16_8(0x558a, 0x00);
			break;
	}
}

void Camera::setSpecialEffect(SPECIAL_EFFECTS effect)
{
	switch(effect)
	{
		case EFFECT_BLUISH:
			this->wrSensorReg16_8(0x5001, 0xff);
			this->wrSensorReg16_8(0x5580, 0x18);
			this->wrSensorReg16_8(0x5585, 0xa0);
			this->wrSensorReg16_8(0x5586, 0x40);
			break;
		case EFFECT_GREENISH:
			this->wrSensorReg16_8(0x5001, 0xff);
			this->wrSensorReg16_8(0x5580, 0x18);
			this->wrSensorReg16_8(0x5585, 0x60);
			this->wrSensorReg16_8(0x5586, 0x60);
			break;
		case EFFECT_REDDISH:
			this->wrSensorReg16_8(0x5001, 0xff);
			this->wrSensorReg16_8(0x5580, 0x18);
			this->wrSensorReg16_8(0x5585, 0x80);
			this->wrSensorReg16_8(0x5586, 0xc0);
			break;
		case EFFECT_BW:
			this->wrSensorReg16_8(0x5001, 0xff);
			this->wrSensorReg16_8(0x5580, 0x18);
			this->wrSensorReg16_8(0x5585, 0x80);
			this->wrSensorReg16_8(0x5586, 0x80);
			break;
		case EFFECT_NEGATIVE:
			this->wrSensorReg16_8(0x5001, 0xff);
			this->wrSensorReg16_8(0x5580, 0x40);
			break;
		case EFFECT_SEPIA:
			this->wrSensorReg16_8(0x5001, 0xff);
			this->wrSensorReg16_8(0x5580, 0x18);
			this->wrSensorReg16_8(0x5585, 0x40);
			this->wrSensorReg16_8(0x5586, 0xa0);
			break;
		case EFFECT_NORMAL:
			this->wrSensorReg16_8(0x5001, 0x7f);
			this->wrSensorReg16_8(0x5580, 0x00);
			break;
	}
}

void Camera::setSharpnessType(SHARPNESS_TYPE sharpness)
{
	switch(sharpness)
	{
		case SHARP_AUTO_DEFAULT:
			this->wrSensorReg16_8(0x530A, 0x00);
			this->wrSensorReg16_8(0x530c, 0x0);
			this->wrSensorReg16_8(0x530d, 0xc);
			this->wrSensorReg16_8(0x5312, 0x40);
			break;
		case SHARP_AUTO_1:
			this->wrSensorReg16_8(0x530A, 0x00);
			this->wrSensorReg16_8(0x530c, 0x4);
			this->wrSensorReg16_8(0x530d, 0x18);
			this->wrSensorReg16_8(0x5312, 0x20);
			break;
		case SHARP_AUTO_2:
			this->wrSensorReg16_8(0x530A, 0x00);
			this->wrSensorReg16_8(0x530c, 0x8);
			this->wrSensorReg16_8(0x530d, 0x30);
			this->wrSensorReg16_8(0x5312, 0x10);
			break;
		case SHARP_MANUAL_OFF:
			this->wrSensorReg16_8(0x530A, 0x08);
			this->wrSensorReg16_8(0x531e, 0x00);
			this->wrSensorReg16_8(0x531f, 0x00);
			break;
		case SHARP_MANUAL_1:
			this->wrSensorReg16_8(0x530A, 0x08);
			this->wrSensorReg16_8(0x531e, 0x04);
			this->wrSensorReg16_8(0x531f, 0x04);
			break;
		case SHARP_MANUAL_2:
			this->wrSensorReg16_8(0x530A, 0x08);
			this->wrSensorReg16_8(0x531e, 0x08);
			this->wrSensorReg16_8(0x531f, 0x08);
			break;
		case SHARP_MANUAL_3:
			this->wrSensorReg16_8(0x530A, 0x08);
			this->wrSensorReg16_8(0x531e, 0x0c);
			this->wrSensorReg16_8(0x531f, 0x0c);
			break;
		case SHARP_MANUAL_4:
			this->wrSensorReg16_8(0x530A, 0x08);
			this->wrSensorReg16_8(0x531e, 0x0f);
			this->wrSensorReg16_8(0x531f, 0x0f);
			break;
		case SHARP_MANUAL_5:
			this->wrSensorReg16_8(0x530A, 0x08);
			this->wrSensorReg16_8(0x531e, 0x1f);
			this->wrSensorReg16_8(0x531f, 0x1f);
			break;
	}
}

void Camera::resetFirmware() {}

void Camera::singleCapture()
{
	this->flushFIFO();
	this->startCapture();
}

void Camera::startCapture() {}