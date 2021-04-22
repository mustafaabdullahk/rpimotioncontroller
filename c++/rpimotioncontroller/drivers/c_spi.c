/*
 * wiringPiSPI.c:
 *	Simplified SPI access routines
 *	Copyright (c) 2012-2015 Gordon Henderson
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as
 *    published by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with wiringPi.
 *    If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <asm/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "c_spi.h"

#define WPI_FATAL  (1 == 1)
#define WPI_ALMOST (1 == 2)

// The SPI bus parameters
//	Variables as they need to be passed as pointers later on

// static const char       *spiDev0  = "/dev/spidev0.0" ;
// static const char       *spiDev1  = "/dev/spidev0.1" ;
static const uint8_t spiBPW = 8;
static const uint16_t spiDelay = 0;

static uint32_t spiSpeeds[2];
static int spiFds[2];

int wiringPiReturnCodes = 0;
/*
 * wiringPiSPIGetFd:
 *	Return the file-descriptor for the given channel
 *********************************************************************************
 */

int wiringPiFailure(int fatal, const char *message, ...)
{
	va_list argp;
	char buffer[1024];

	if (!fatal && wiringPiReturnCodes)
		return -1;

	fprintf(stderr, "%s", buffer);
	exit(EXIT_FAILURE);

	return 0;
}

int spiGetFd(int channel)
{
	return spiFds[channel & 1];
}

/*
 * wiringPiSPIDataRW:
 *	Write and Read a block of data over the SPI bus.
 *	Note the data ia being read into the transmit buffer, so will
 *	overwrite it!
 *	This is also a full-duplex operation.
 *********************************************************************************
 */

int spiDataRW(int channel, unsigned char *data, int len)
{
	struct spi_ioc_transfer spi;

	channel &= 1;

	// Mentioned in spidev.h but not used in the original kernel documentation
	//	test program )-:

	memset(&spi, 0, sizeof(spi));

	spi.tx_buf = (unsigned long)data;
	spi.rx_buf = (unsigned long)data;
	spi.len = len;
	spi.delay_usecs = spiDelay;
	spi.speed_hz = spiSpeeds[channel];
	spi.bits_per_word = spiBPW;

	return ioctl(spiFds[channel], SPI_IOC_MESSAGE(1), &spi);
}

/*
 * wiringPiSPISetupMode:
 *	Open the SPI device, and set it up, with the mode, etc.
 *********************************************************************************
 */

int spiSetupMode(int channel, int speed, int mode)
{
	int fd;
	char spiDev[32];

	mode &= 3; // Mode is 0, 1, 2 or 3

	// Channel can be anything - lets hope for the best
	//  channel &= 1 ;	// Channel is 0 or 1

	snprintf(spiDev, 31, "/dev/spidev0.%d", channel);

	if ((fd = open(spiDev, O_RDWR)) < 0) {
		//gWarn("spi device not setting. %s:" , strerror(fd));
		return 5;
	}

	spiSpeeds[channel] = speed;
	spiFds[channel] = fd;
	// Set SPI parameters.
	
	if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0){
		//gWarn("spi device not setting. %s:", strerror(fd));
		return fd;
	}

	if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spiBPW) < 0){
		//gWarn("spi device not setting. %s:" ,strerror(fd));
		return fd;
	}

	if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0){
		//gWarn("spi device not setting. %s:" ,strerror(fd));
		return fd;
	}

	return fd;
}

/*
 * wiringPiSPISetup:
 *	Open the SPI device, and set it up, etc. in the default MODE 0
 *********************************************************************************
 */

int spiSetup(int channel, int speed)
{
	return spiSetupMode(channel, speed, 0);
}
