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

#ifndef CAMERA_H
#define CAMERA_H

#include "SPIDriver.h"
#include "I2CDriver.h"
#include "Timer.h"

#ifdef RPi4
#include "RPi4SPI.h"
#include "RPi4I2C.h"
#include "RPi4Timer.h"
#else
#error Board input does not exist
#endif

enum BUFFER_SIZE
{
	JPEG_BUFFER_SIZE = 2 * 1024 * 1024,
	CMD_BUFFER_SIZE	 = 512
};

enum CHIPID_LEVEL
{
	CHIPID_HIGH = 0x300a,
	CHIPID_LOW	= 0x300b
};

enum IMAGE_TYPE
{
	IMG_BMP = 0,
	IMG_JPEG,
	IMG_RAW
};

enum RESOLUTION
{
	RES_320x240 = 0,	// 320x240
	RES_640x480,		// 640x480
	RES_1024x768,		// 1024x768
	RES_1280x960,		// 1280x960
	RES_1600x1200,		// 1600x1200
	RES_2048x1536,		// 2048x1536
	RES_2592x1944		// 2592x1944
};

enum LIGHT_MODE
{
	MODE_AUTO = 0,
	MODE_SUNNY,
	MODE_CLOUDY,
	MODE_OFFICE,
	MODE_HOME
};

enum ADVANCED_LIGHT_MODE
{
	MODE_ADVANCED_AWB = 0,
	MODE_SIMPLE_AWB,
	MODE_MANUAL_DAY,
	MODE_MANUAL_A,
	MODE_MANUAL_CWF,
	MODE_MANUAL_CLOUDY
};

enum COLOR_SATURATION
{
	SAT_4 = 0,
	SAT_3,
	SAT_2,
	SAT_1,
	SAT_0,
	SAT_NEG_1,
	SAT_NEG_2,
	SAT_NEG_3,
	SAT_NEG_4
};

enum BRIGHTNESS
{
	BRIGHTNESS_4 = 0,
	BRIGHTNESS_3,
	BRIGHTNESS_2,
	BRIGHTNESS_1,
	BRIGHTNESS_0,
	BRIGHTNESS_NEG_1,
	BRIGHTNESS_NEG_2,
	BRIGHTNESS_NEG_3,
	BRIGHTNESS_NEG_4
};

enum CONTRAST
{
	CONTRAST_4 = 0,
	CONTRAST_3,
	CONTRAST_2,
	CONTRAST_1,
	CONTRAST_0,
	CONTRAST_NEG_1,
	CONTRAST_NEG_2,
	CONTRAST_NEG_3,
	CONTRAST_NEG_4
};

enum ROTATION
{
	DEG_NEG_180 = 0,
	DEG_NEG_150,
	DEG_NEG_120,
	DEG_NEG_90,
	DEG_NEG_60,
	DEG_NEG_30,
	DEG_0,
	DEG_30,
	DEG_60,
	DEG_90,
	DEG_120,
	DEG_150
};

enum SPECIAL_EFFECTS
{
	EFFECT_BLUISH,
	EFFECT_GREENISH,
	EFFECT_REDDISH,
	EFFECT_BW,
	EFFECT_NEGATIVE,
	EFFECT_NORMAL,
	EFFECT_SEPIA,
};

enum EXPOSURE
{
	EXP_NEG_17_EV = 0,
	EXP_NEG_13_EV,
	EXP_NEG_10_EV,
	EXP_NEG_07_EV,
	EXP_NEG_03_EV,
	EXP_DEFAULT,
	EXP_07_EV,
	EXP_10_EV,
	EXP_13_EV,
	EXP_17_EV,
	EXP_03_EV
};

enum SHARPNESS_TYPE
{
	SHARP_AUTO_DEFAULT = 0,
	SHARP_AUTO_1,
	SHARP_AUTO_2,
	SHARP_MANUAL_OFF,
	SHARP_MANUAL_1,
	SHARP_MANUAL_2,
	SHARP_MANUAL_3,
	SHARP_MANUAL_4,
	SHARP_MANUAL_5
};

enum SHARPNESS_LEVEL
{
	SHARP_1 = 0,
	SHARP_2,
	SHARP_3,
	SHARP_4,
	SHARP_5,
	SHARP_6,
	SHARP_7,
	SHARP_8,
	SHARP_AUTO
};

enum EV
{
	EV_3 = 0,
	EV_2,
	EV_1,
	EV_0,
	EV_NEG_1,
	EV_NEG_2,
	EV_NEG_3
};

enum FLIP
{
	FLIP_HORIZONTAL = 0,
	FLIP_VERTICAL,
	FLIP_BOTH
};

enum QUALITY
{
	QUALITY_HIGH = 0,
	QUALITY_DEFAULT,
	QUALITY_LOW
};

enum COLOR_TYPE
{
	COLOR_BAR = 0,
	COLOR_SQUARE,
	COLOR_BW_SQUARE,
	COLOR_DLI
};

enum NIGHT_MODE
{
	NIGHT_MODE_ON = 0,
	NIGHT_MODE_OFF
};

enum FRAMERATE_DETECT
{
	FRAMERATE_OFF = 0,
	FRAMERATE_MANUAL_50HZ,
	FRAMERATE_MANUAL_60HZ,
	FRAMERATE_AUTO_DETECT
};

class Camera
{
  private:
	PIN			 csPin;
	unsigned int currentLength;
	IMAGE_TYPE	 format;

	char readBuffer[JPEG_BUFFER_SIZE];
	char commandBuffer[CMD_BUFFER_SIZE];

	char * sendBuffer;

#ifdef RPi4
	RPi4SPI	  spiDriver;
	RPi4I2C	  i2cDriver;
	RPi4Timer timer;
#else
	SPIDriver spiDriver;
	I2CDriver i2cDriver;
	Timer	  timer;
#endif

	unsigned char sensorAddress = 0;

	void		  clearFIFOFlag();
	unsigned char readFIFO();
	void		  flushFIFO();
	unsigned int  readFIFOLength();
	void		  setFIFOBurst();

	unsigned char readRegister(unsigned char address);
	void		  writeRegister(unsigned char address, unsigned char data);

	void		  setBit(unsigned char address, unsigned char bit);
	void		  clearBit(unsigned char address, unsigned char bit);
	unsigned char getBit(unsigned char address, unsigned char bit);

	unsigned char busWrite(int address, int value);
	unsigned char busRead(int address);

	unsigned char wrSensorReg8_8(int regID, int regDat);
	int			  wrSensorRegs8_8(const struct sensor_reg *);
	unsigned char rdSensorReg8_8(unsigned char regID, unsigned char * regDat);

	unsigned char wrSensorReg16_8(int regID, int regDat);
	int			  wrSensorRegs16_8(const struct sensor_reg reglist[]);
	unsigned char rdSensorReg16_8(unsigned int regID, unsigned char * regDat);
	int			  rdSensorRegs16_8(const struct sensor_reg reglist[]);

  public:
	Camera(unsigned int cs);
	Camera();
	~Camera() = default;

	void init();

	void activate();
	void deactivate();

	void setImageFormat(IMAGE_TYPE format);
	void setResolution(RESOLUTION res);
	void setColorSaturation(COLOR_SATURATION sat);
	void setBrightness(BRIGHTNESS level);
	void setSpecialEffect(SPECIAL_EFFECTS effect);
	void setSharpnessType(SHARPNESS_TYPE sharpness);

	void resetFirmware();
	void singleCapture();
	void startCapture();
};

#endif