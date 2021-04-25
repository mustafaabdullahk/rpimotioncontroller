#include "dac8532.h"
#include"drivercontext.h"
#include "config.h"

dac8532::dac8532(QObject *parent) : QObject(parent)
{
}

void dac8532::configModule(uint8_t channel, uint16_t data)
{
	//config cfg;
	DriverContext::instance().Configure()->digitalWrite(CS_DAC_PIN, 1);
	DriverContext::instance().Configure()->digitalWrite(CS_DAC_PIN, 0);
	DriverContext::instance().Configure()->spiWriteByte(channel);
	DriverContext::instance().Configure()->spiWriteByte((data >> 8));
	DriverContext::instance().Configure()->spiWriteByte((data & 0xff));
	DriverContext::instance().Configure()->digitalWrite(CS_DAC_PIN, 1);
}

void dac8532::outVoltage(uint8_t channel, float voltage)
{
	uint16_t temp = 0;
	if ((voltage <= DAC_VREF) && (voltage >= 0)) {
		temp = (uint16_t)(voltage * DAC_Value_MAX / DAC_VREF);
		configModule(channel, temp);
	}
}
