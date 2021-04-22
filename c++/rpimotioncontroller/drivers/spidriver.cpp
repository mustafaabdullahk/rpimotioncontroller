#include "spidriver.h"
#include "3rdparty/debug.h"
#include <QDebug>

spidriver::spidriver(int channel, int mode, int bit, int speed)
{
	spiChannel = channel;
	spiMode = mode;
	spiBit = bit;
	spiSpeed = speed;
	if(!spiSetup())
		isConnected = true;
	else 
		isConnected = false;
}

int spidriver::spiSetup()
{
	std::string device = "/dev/spidev0.";
	device.append(std::to_string(spiChannel));
	
	if ((fd = open(device.data(), O_RDWR)) < 0) {
		gWarn("The SPI device has opening error, %s. %s", device.data(),
			  strerror(fd));
		return errno;
	}
	if (ioctl(fd, SPI_IOC_WR_MODE, &spiMode) < 0) {
		gWarn("The SPI device has mode setting error, %s. %s", device.data(),
			  strerror(fd));
		return errno;
	}
	if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &spiBit) < 0) {
		gWarn("The SPI device has bit priority setting error, %s. %s", device.data(),
			  strerror(fd));
		return errno;
	}
	if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spiSpeed) < 0) {
		gWarn("The SPI device has speed setting error, %s. %s",
			  device.data(), strerror(fd));
		return errno;
	}
	return 0;
}

int spidriver::spiWriteByte(unsigned char *data, int len)
{
	struct spi_ioc_transfer spi;
	memset(&spi, 0, sizeof(spi));
		spi.tx_buf = (unsigned long)data;
	spi.rx_buf = (unsigned long)data;
	spi.len = len;
	spi.delay_usecs = 0; //TO DO add spi delay arg
	spi.speed_hz = spiSpeed;
	spi.bits_per_word = spiBit;
	if (ioctl(fd, SPI_IOC_MESSAGE(1), &spi) < 0) {
		gWarn("The SPI device has writing error,  %s", strerror(fd));
	}
	return 0;
}

bool spidriver::spiIsConnected() const
{
	return isConnected;
}
