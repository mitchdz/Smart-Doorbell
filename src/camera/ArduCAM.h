/*
 * Copyright (c) 2020, Arducam Technology Co., Ltd <http://www.arducam.com>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *		* Redistributions of source code must retain the above copyright
 *			notice, this list of conditions and the following disclaimer.
 * 		* Redistributions in binary form must reproduce the above copyright
 * 			notice, this list of conditions and the following disclaimer in the
 * 			documentation and/or other materials provided with the distribution.
 * 		* Neither the name of the copyright holder nor the
 * 			names of its contributors may be used to endorse or promote products
 * 			derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ARDUCAM_H
#define __ARDUCAM_H

#define JPEG_BUF_SIZE   2*1024*1024 //2M
#define CMD_BUF_SIZE    512


char readbuf[JPEG_BUF_SIZE];


char* sendbuf_cam1 ;
char* sendbuf_cam2 ;
char* sendbuf_cam3 ;
char* sendbuf_cam4 ;



char revCmdData[CMD_BUF_SIZE];

//ArduCAM CS define
#define     CAM_CS1         17
#define     CAM_CS2         23
#define     CAM_CS3         22
#define     CAM_CS4         24




#include "bcm283x_board_driver.h"

#define OV2640_CHIPID_HIGH 	0x0A
#define OV2640_CHIPID_LOW 	0x0B

#define OV5642_CHIPID_HIGH 0x300a
#define OV5642_CHIPID_LOW  0x300b

#define OV5640_CHIPID_HIGH 0x300a
#define OV5640_CHIPID_LOW  0x300b

extern unsigned char sensor_model;
extern unsigned char sensor_addr;
extern unsigned int length;
extern unsigned char is_header;
#define BMP 	    0
#define JPEG	    1
#define RAW         2

#define OV7670		0	
#define MT9D111_A	1
#define OV7675		2
#define OV5642		3
#define OV3640  	4
#define OV2640  	5
#define OV9655		6
#define MT9M112		7
#define OV7725		8
#define OV7660		9
#define MT9M001 	10
#define OV5640 		11
#define MT9D111_B	12
#define OV9650		13
#define MT9V111		14
#define MT9T112		15
#define MT9D112		16

#define OV5642_320x240 		0	//320x240
#define OV5642_640x480		1	//640x480
#define OV5642_1024x768		2	//1024x768
#define OV5642_1280x960 	3	//1280x960
#define OV5642_1600x1200	4	//1600x1200
#define OV5642_2048x1536	5	//2048x1536
#define OV5642_2592x1944	6	//2592x1944

//Light Mode

#define Auto                 0
#define Sunny                1
#define Cloudy               2
#define Office               3
#define Home                 4

#define Advanced_AWB         0
#define Simple_AWB           1
#define Manual_day           2
#define Manual_A             3
#define Manual_cwf           4
#define Manual_cloudy        5



//Color Saturation 

#define Saturation4          0
#define Saturation3          1
#define Saturation2          2
#define Saturation1          3
#define Saturation0          4
#define Saturation_1         5
#define Saturation_2         6
#define Saturation_3         7
#define Saturation_4         8

//Brightness

#define Brightness4          0
#define Brightness3          1
#define Brightness2          2
#define Brightness1          3
#define Brightness0          4
#define Brightness_1         5
#define Brightness_2         6
#define Brightness_3         7
#define Brightness_4         8


//Contrast

#define Contrast4            0
#define Contrast3            1
#define Contrast2            2
#define Contrast1            3
#define Contrast0            4
#define Contrast_1           5
#define Contrast_2           6
#define Contrast_3           7
#define Contrast_4           8



#define degree_180            0
#define degree_150            1
#define degree_120            2
#define degree_90             3
#define degree_60             4
#define degree_30             5
#define degree_0              6
#define degree30              7
#define degree60              8
#define degree90              9
#define degree120             10
#define degree150             11



//Special effects

#define Antique                      0
#define Bluish                       1
#define Greenish                     2
#define Reddish                      3
#define BW                           4
#define Negative                     5
#define BWnegative                   6
#define Normal                       7
#define Sepia                        8
#define Overexposure                 9
#define Solarize                     10
#define  Blueish                     11
#define Yellowish                    12

#define Exposure_17_EV                    0
#define Exposure_13_EV                    1
#define Exposure_10_EV                    2
#define Exposure_07_EV                    3
#define Exposure_03_EV                    4
#define Exposure_default                  5
#define Exposure07_EV                     6
#define Exposure10_EV                     7
#define Exposure13_EV                     8
#define Exposure17_EV                     9
#define Exposure03_EV                     10


#define Auto_Sharpness_default              0
#define Auto_Sharpness1                     1
#define Auto_Sharpness2                     2
#define Manual_Sharpnessoff                 3
#define Manual_Sharpness1                   4
#define Manual_Sharpness2                   5
#define Manual_Sharpness3                   6
#define Manual_Sharpness4                   7
#define Manual_Sharpness5                   8



#define Sharpness1                         0
#define Sharpness2                         1
#define Sharpness3                         2
#define Sharpness4                         3
#define Sharpness5                         4
#define Sharpness6                         5
#define Sharpness7                         6
#define Sharpness8                         7
#define Sharpness_auto                     8




#define EV3                                 0
#define EV2                                 1
#define EV1                                 2
#define EV0                                 3
#define EV_1                                4
#define EV_2                                5
#define EV_3                                6

#define MIRROR                              0
#define FLIP                                1
#define MIRROR_FLIP                         2




#define high_quality                         0
#define default_quality                      1
#define low_quality                          2

#define Color_bar                      0
#define Color_square                   1
#define BW_square                      2
#define DLI                            3


#define Night_Mode_On                  0
#define Night_Mode_Off                 1

#define Off                            0
#define Manual_50HZ                    1
#define Manual_60HZ                    2
#define Auto_Detection                 3


/****************************************************/
/* I2C Control Definition 													*/
/****************************************************/
#define I2C_ADDR_8BIT 0
#define I2C_ADDR_16BIT 1
#define I2C_REG_8BIT 0
#define I2C_REG_16BIT 1
#define I2C_DAT_8BIT 0
#define I2C_DAT_16BIT 1

/* Register initialization tables for SENSORs */
/* Terminating list entry for reg */
#define SENSOR_REG_TERM_8BIT                0xFF
#define SENSOR_REG_TERM_16BIT               0xFFFF
/* Terminating list entry for val */
#define SENSOR_VAL_TERM_8BIT                0xFF
#define SENSOR_VAL_TERM_16BIT               0xFFFF

//Define maximum frame buffer size
#if (defined OV2640_MINI_2MP)
#define MAX_FIFO_SIZE		0x5FFFF			//384Kunsigned char
#elif (defined OV5642_MINI_5MP || defined OV5642_MINI_5MP_BIT_ROTATION_FIXED || defined ARDUCAM_SHIELD_REVC)
#define MAX_FIFO_SIZE		0x7FFFF			//512Kunsigned char
#else
#define MAX_FIFO_SIZE		0x7FFFFF		//8Munsigned char
#endif 

/****************************************************/
/* ArduChip registers definition 											*/
/****************************************************/
#define RWBIT									0x80  //READ AND WRITE BIT IS BIT[7]

#define ARDUCHIP_TEST1       	0x00  //TEST register

#if !(defined OV2640_MINI_2MP)
	#define ARDUCHIP_FRAMES			  0x01  //FRAME control register, Bit[2:0] = Number of frames to be captured																		//On 5MP_Plus platforms bit[2:0] = 7 means continuous capture until frame buffer is full
#endif

#define ARDUCHIP_MODE      		0x02  //Mode register
#define MCU2LCD_MODE       		0x00
#define CAM2LCD_MODE       		0x01
#define LCD2MCU_MODE       		0x02

#define ARDUCHIP_TIM       		0x03  //Timming control
#if !(defined OV2640_MINI_2MP)
	#define HREF_LEVEL_MASK    		0x01  //0 = High active , 		1 = Low active
	#define VSYNC_LEVEL_MASK   		0x02  //0 = High active , 		1 = Low active
	#define LCD_BKEN_MASK      		0x04  //0 = Enable, 					1 = Disable
	#if (defined ARDUCAM_SHIELD_V2)
		#define PCLK_REVERSE_MASK  	0x08  //0 = Normal PCLK, 		1 = REVERSED PCLK
	#else
		#define PCLK_DELAY_MASK  		0x08  //0 = data no delay,		1 = data delayed one PCLK
	#endif
#endif

#define ARDUCHIP_FIFO      		0x04  //FIFO and I2C control
#define FIFO_CLEAR_MASK    		0x01
#define FIFO_START_MASK    		0x02
#define FIFO_RDPTR_RST_MASK     0x10
#define FIFO_WRPTR_RST_MASK     0x20

#define ARDUCHIP_GPIO			  0x06  //GPIO Write Register
#if !(defined (ARDUCAM_SHIELD_V2) || defined (ARDUCAM_SHIELD_REVC))
#define GPIO_RESET_MASK			0x01  //0 = Sensor reset,							1 =  Sensor normal operation
#define GPIO_PWDN_MASK			0x02  //0 = Sensor normal operation, 	1 = Sensor standby
#define GPIO_PWREN_MASK			0x04	//0 = Sensor LDO disable, 			1 = sensor LDO enable
#endif

#define BURST_FIFO_READ			0x3C  //Burst FIFO read operation
#define SINGLE_FIFO_READ		0x3D  //Single FIFO read operation

#define ARDUCHIP_REV       		0x40  //ArduCHIP revision
#define VER_LOW_MASK       		0x3F
#define VER_HIGH_MASK      		0xC0

#define ARDUCHIP_TRIG      		0x41  //Trigger source
#define VSYNC_MASK         		0x01
#define SHUTTER_MASK       		0x02
#define CAP_DONE_MASK      		0x08

#define FIFO_SIZE1				0x42  //Camera write FIFO size[7:0] for burst to read
#define FIFO_SIZE2				0x43  //Camera write FIFO size[15:8]
#define FIFO_SIZE3				0x44  //Camera write FIFO size[18:16]

#ifndef _SENSOR_
#define _SENSOR_
struct sensor_reg {
	unsigned int reg;
	unsigned int val;
};
#endif
#endif
