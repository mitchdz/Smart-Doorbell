# Copyright (c) 2021 Lena Voytek
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# PREFIX is environment variable, but if it is not set, then set default value
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

SHELL := /bin/bash

LIBARGS ?= -c -fpic
CXXFLAGS ?= -Wall -Werror

OUTDIR ?= build

BOARD ?= RPi4
DEBUG ?= false

.PHONY:all
all:$(OUTDIR)/smart-doorbell

# Smart Doorbell CLI app creation
$(OUTDIR)/smart-doorbell:$(OUTDIR)/libCamera.so $(OUTDIR)/include/Camera.h
	$(CXX) -Wl,-R -Wl,$(CURDIR)/$(OUTDIR) $(CXXFLAGS) -D$(BOARD) -I$(OUTDIR)/include -L$(OUTDIR) -lCamera -lBoard -lTimer -lGPIO -lI2C -lSPI -I$(OUTDIR)/include -o $@ src/main/SmartDoorbellCLI.cpp


# ArduCAM Library
$(OUTDIR)/libCamera.so:$(OUTDIR)/libTimer.so $(OUTDIR)/include/$(BOARD)Timer.h $(OUTDIR)/libGPIO.so $(OUTDIR)/include/$(BOARD)GPIO.h $(OUTDIR)/libI2C.so $(OUTDIR)/include/$(BOARD)I2C.h $(OUTDIR)/libSPI.so $(OUTDIR)/include/$(BOARD)SPI.h src/camera
	$(CXX) $(LIBARGS) $(CXXFLAGS) -D$(BOARD) -L$(OUTDIR) -lBoard -lTimer -lGPIO -lI2C -lSPI -I$(OUTDIR)/include src/camera/Camera.cpp -o $(OUTDIR)/camera.o
	$(CXX) -shared -o $@ $(OUTDIR)/camera.o

$(OUTDIR)/include/Camera.h:src/camera
	cp src/camera/ArduCAM.h $(OUTDIR)/include/
	cp src/camera/Camera.h $(OUTDIR)/include/
	cp src/camera/ov5642_regs.h $(OUTDIR)/include/

# SPI Library
$(OUTDIR)/libSPI.so:$(OUTDIR)/libBoard.so $(OUTDIR)/include/$(BOARD).h $(OUTDIR)/libGPIO.so $(OUTDIR)/include/$(BOARD)GPIO.h src/SPI
	$(CXX) $(LIBARGS) $(CXXFLAGS) -D$(BOARD) -L$(OUTDIR) -lBoard -lGPIO -I$(OUTDIR)/include src/SPI/$(BOARD)SPI.cpp -o $(OUTDIR)/SPI.o
	$(CXX) -shared -o $@ $(OUTDIR)/SPI.o

$(OUTDIR)/include/$(BOARD)SPI.h:src/SPI
	cp src/SPI/$(BOARD)SPI.h $(OUTDIR)/include/
	cp src/SPI/SPIDriver.h $(OUTDIR)/include/

# I2C Library
$(OUTDIR)/libI2C.so:$(OUTDIR)/libBoard.so $(OUTDIR)/include/$(BOARD).h $(OUTDIR)/libTimer.so $(OUTDIR)/include/$(BOARD)Timer.h $(OUTDIR)/libGPIO.so $(OUTDIR)/include/$(BOARD)GPIO.h src/I2C
	$(CXX) $(LIBARGS) $(CXXFLAGS) -D$(BOARD) -L$(OUTDIR) -lBoard -lTimer -lGPIO -I$(OUTDIR)/include src/I2C/$(BOARD)I2C.cpp -o $(OUTDIR)/I2C.o
	$(CXX) -shared -o $@ $(OUTDIR)/I2C.o

$(OUTDIR)/include/$(BOARD)I2C.h:src/I2C
	cp src/I2C/$(BOARD)I2C.h $(OUTDIR)/include/
	cp src/I2C/I2CDriver.h $(OUTDIR)/include/

# GPIO Library
$(OUTDIR)/libGPIO.so:$(OUTDIR)/libBoard.so $(OUTDIR)/include/$(BOARD).h src/GPIO
	$(CXX) $(LIBARGS) $(CXXFLAGS) -D$(BOARD) -L$(OUTDIR) -lBoard -I$(OUTDIR)/include src/GPIO/$(BOARD)GPIO.cpp -o $(OUTDIR)/GPIO.o
	$(CXX) -shared -o $@ $(OUTDIR)/GPIO.o

$(OUTDIR)/include/$(BOARD)GPIO.h:src/GPIO
	cp src/GPIO/$(BOARD)GPIO.h $(OUTDIR)/include/
	cp src/GPIO/GPIODriver.h $(OUTDIR)/include/

# Timer Library
$(OUTDIR)/libTimer.so:$(OUTDIR)/libBoard.so $(OUTDIR)/include/$(BOARD).h src/timer
	$(CXX) $(LIBARGS) $(CXXFLAGS) -D$(BOARD) -L$(OUTDIR) -lBoard -I$(OUTDIR)/include src/timer/$(BOARD)Timer.cpp -o $(OUTDIR)/timer.o
	$(CXX) -shared -o $@ $(OUTDIR)/timer.o

$(OUTDIR)/include/$(BOARD)Timer.h:src/timer
	cp src/timer/$(BOARD)Timer.h $(OUTDIR)/include/
	cp src/timer/Timer.h $(OUTDIR)/include/

# Board Definitions Library
$(OUTDIR)/libBoard.so:src/board
	mkdir -p $(OUTDIR)/
	$(CXX) $(LIBARGS) $(CXXFLAGS) -D$(BOARD) src/board/$(BOARD).cpp -o $(OUTDIR)/board.o
	$(CXX) -shared -o $@ $(OUTDIR)/board.o

$(OUTDIR)/include/$(BOARD).h:src/board
	mkdir -p $(OUTDIR)/include
	cp src/board/$(BOARD).h $(OUTDIR)/include/

.PHONY:install
install:
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(OUTDIR)/libCamera.so $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(OUTDIR)/libSPI.so $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(OUTDIR)/libI2C.so $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(OUTDIR)/libGPIO.so $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(OUTDIR)/libTimer.so $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $(OUTDIR)/libBoard.so $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/
	install -m 644 $(OUTDIR)/include/$(BOARD).h $(DESTDIR)$(PREFIX)/include/
	install -m 644 $(OUTDIR)/include/$(BOARD)SPI.h $(DESTDIR)$(PREFIX)/include/
	install -m 644 $(OUTDIR)/include/Camera.h $(DESTDIR)$(PREFIX)/include/
	install -m 644 $(OUTDIR)/include/$(BOARD)I2C.h $(DESTDIR)$(PREFIX)/include/
	install -m 644 $(OUTDIR)/include/$(BOARD)GPIO.h $(DESTDIR)$(PREFIX)/include/
	install -m 644 $(OUTDIR)/include/$(BOARD)Timer.h $(DESTDIR)$(PREFIX)/include/
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 644 $(OUTDIR)/smart-doorbell $(DESTDIR)$(PREFIX)/bin/

.PHONY:clean
clean:
	rm -rf $(OUTDIR)/
