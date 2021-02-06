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
 * I2CDriver
 *
 * This module acts as a parent class for drivers that control the I2C protocol on
 * specific boards
 */

#ifndef I2CDRIVER_H
#define I2CDRIVER_H

class I2CDriver
{
  protected:
	virtual void SCL_HIGH();
	virtual void SCL_LOW();
	virtual void SDA_HIGH();
	virtual void SDA_LOW();

  public:
	virtual void		  init();
	virtual void		  start();
	virtual void		  stop();
	virtual void		  sendNACK();
	virtual void		  sendACK();
	virtual unsigned char write(unsigned char data);
	virtual unsigned char read();
};

inline void			 I2CDriver::SCL_HIGH() {}
inline void			 I2CDriver::SCL_LOW() {}
inline void			 I2CDriver::SDA_HIGH() {}
inline void			 I2CDriver::SDA_LOW() {}
inline void			 I2CDriver::init() {}
inline void			 I2CDriver::start() {}
inline void			 I2CDriver::stop() {}
inline void			 I2CDriver::sendNACK() {}
inline void			 I2CDriver::sendACK() {}
inline unsigned char I2CDriver::write(unsigned char data) { return 0; }
inline unsigned char I2CDriver::read() { return 0; }

#endif