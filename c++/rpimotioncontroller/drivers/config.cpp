#include "3rdparty/debug.h"
#include "drivers/spidriver.h"
#include "drivers/gpiodriver.h"
#include "config.h"

#include <QDebug>

config::config()
{
//	cleanup();
//	int state = setup();
//	qDebug()<<  "Setup state:" << state;
//	setup_gpio(RST_PIN, OUTPUT, PUD_OFF);
//	setup_gpio(CS_DAC_PIN, OUTPUT, PUD_OFF);
//	setup_gpio(CS_PIN, OUTPUT, PUD_OFF);
//	setup_gpio(DRDY_PIN, INPUT, PUD_OFF);
	
	gpio.gpioExport(RST_PIN);
	gpio.gpioExport(CS_DAC_PIN);
	gpio.gpioExport(CS_PIN);
	gpio.gpioExport(DRDY_PIN);
	gpio.gpioSetMode(RST_PIN, OUTPUT);
	gpio.gpioSetMode(CS_DAC_PIN, OUTPUT);
	gpio.gpioSetMode(CS_PIN, OUTPUT);
	gpio.gpioSetMode(DRDY_PIN,INPUT);
//	spiSetupMode(0, 3200000, 1);
	qDebug() << "hereee";
	spi = new spidriver(0, SPI_MODE_1, 8, 200000);
	qDebug() << "spi setup state: " << spi->spiIsConnected();
}

void config::digitalWrite(int pin, int value)
{
//	output_gpio(pin, value);
	gpio.gpioSetValue(pin, value);
}

int config::digitalRead(int pin)
{
	return gpio.gpioGetValue(pin);
//	return input_gpio(pin);
}

int config::spiWriteByte(uint8_t data)
{
	int readData;
//	readData = spiDataRW(0, &data, 1);
	readData = spi->spiTransfer(&data, 1);
	if (readData < 0) {
		gInfoS() << "spi data write operation failed.";
	}
	return readData;
}

uint8_t config::spiReadByte()
{
	uint8_t readData, value = 0xff;
//	readData = spiDataRW(0, &value, 1);
	readData = spi->spiTransfer(&value, 1);
	if (readData < 0) {
		gInfoS() << "spi data read operation failed.";
	}
	return value;
}
