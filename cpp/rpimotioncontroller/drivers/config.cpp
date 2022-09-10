#include "config.h"
#include "3rdparty/debug.h"
#include "gpiodriver.h"
#include "spidriver.h"

#include <QDebug>

config::config()
{
	gpio.gpioExport(RST_PIN);
	gpio.gpioExport(CS_DAC_PIN);
	gpio.gpioExport(CS_PIN);
	gpio.gpioExport(DRDY_PIN);
	gpio.gpioSetMode(RST_PIN, OUTPUT);
	gpio.gpioSetMode(CS_DAC_PIN, OUTPUT);
	gpio.gpioSetMode(CS_PIN, OUTPUT);
	gpio.gpioSetMode(DRDY_PIN, INPUT);
	spi = new spidriver(0, SPI_MODE_1, 8, 200000);
	gWarn("spi driver setup state : %s",
		  std::to_string(spi->spiIsConnected()).data());
}

void config::digitalWrite(int pin, int value)
{
	gpio.gpioSetValue(pin, value);
}

int config::digitalRead(int pin)
{
	return gpio.gpioGetValue(pin);
}

int config::spiWriteByte(uint8_t data)
{
	int readData;
	readData = spi->spiTransfer(&data, 1);
	if (readData < 0) {
		gInfoS() << "spi data write operation failed.";
	}
	return readData;
}

uint8_t config::spiReadByte()
{
	uint8_t readData, value = 0xff;
	readData = spi->spiTransfer(&value, 1);
	if (readData < 0) {
		gInfoS() << "spi data read operation failed.";
	}
	return value;
}
