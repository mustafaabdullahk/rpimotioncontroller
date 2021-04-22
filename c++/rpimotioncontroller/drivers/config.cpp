extern "C" {
#include "drivers/c_gpio.h"
}
#include "3rdparty/debug.h"
#include "drivers/c_spi.h"
#include "config.h"

#include <QDebug>

config::config()
{
	int state = setup();
	qDebug()<<  "Setup state:" << state;
	setup_gpio(RST_PIN, OUTPUT, PUD_OFF);
	setup_gpio(CS_DAC_PIN, OUTPUT, PUD_OFF);
	setup_gpio(CS_PIN, OUTPUT, PUD_OFF);
	setup_gpio(DRDY_PIN, INPUT, PUD_UP);
	qDebug() << "spi setup state: " << spiSetupMode(0, 3200000, 1);
}

void config::digitalWrite(int pin, int value)
{
	output_gpio(pin, value);
}

int config::spiWriteByte(uint8_t data)
{
	int readData;
	readData = spiDataRW(0, &data, 1);
	if (readData < 0) {
		gInfoS() << "spi data write operation failed.";
	}
	return readData;
}

uint8_t config::spiReadByte()
{
	uint8_t readData, value = 0xff;
	readData = spiDataRW(0, &value, 1);
	if (readData < 0) {
		gInfoS() << "spi data read operation failed.";
	}
	return value;
}