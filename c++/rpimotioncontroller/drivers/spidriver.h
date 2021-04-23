#ifndef SPIDRIVER_H
#define SPIDRIVER_H

#include <asm/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <string>

class spidriver
{
public:
	spidriver(int channel, int mode, int bit, int speed);
	int spiSetup();
	int spiTransfer(unsigned char* data, int len);
	int spiReadByte();
	bool spiIsConnected() const;
protected:
	int fd;
	int spiChannel;
	int spiMode;
	int spiBit;
	int spiSpeed;
	bool isConnected = false;
};

#endif // SPIDRIVER_H