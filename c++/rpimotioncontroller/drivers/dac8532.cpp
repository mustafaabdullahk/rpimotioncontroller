#include "dac8532.h"
#include "config.h"

dac8532::dac8532(QObject *parent) : QObject(parent)
{
}

void dac8532::configModule(uint8_t channel, uint16_t data)
{
	config cfg;
	cfg.digitalWrite(CS_DAC_PIN, 1);
	cfg.digitalWrite(CS_DAC_PIN, 0);
	cfg.spiWriteByte(channel);
	cfg.spiWriteByte((data >> 8));
	cfg.spiWriteByte((data & 0xff));
	cfg.digitalWrite(CS_DAC_PIN, 1);
}

void dac8532::outVoltage(uint8_t channel, float voltage)
{
	uint16_t temp = 0;
	if ((voltage <= DAC_VREF) && (voltage >= 0)) {
		temp = (uint16_t)(voltage * DAC_Value_MAX / DAC_VREF);
		configModule(channel, temp);
	}
}
