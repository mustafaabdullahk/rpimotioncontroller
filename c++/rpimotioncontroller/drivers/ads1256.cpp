#include "ads1256.h"
#include "3rdparty/debug.h"
#include "drivercontext.h"
#include <thread>

ads1256::ads1256(QObject *parent) : QObject(parent)
{
	init();
}

quint8 ads1256::init()
{
	reset();
	if (readChipID() == 3) {
		gInfoS() << "id read succesfully";
	} else {
		gInfoS() << "id read failed";
		return 1;
	}
	configure(ADS1256_GAIN_64, ADS1256_100SPS);
	return 0;
}

void ads1256::reset()
{
	DriverContext::instance().Configure()->digitalWrite(RST_PIN, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	DriverContext::instance().Configure()->digitalWrite(RST_PIN, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	DriverContext::instance().Configure()->digitalWrite(RST_PIN, 1);
}

void ads1256::setMode(quint8 mode)
{
	
}

void ads1256::writeCommand(quint8 cmd)
{
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 0);
	DriverContext::instance().Configure()->spiWriteByte(cmd);
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 1);
}

void ads1256::writeRegister(quint8 reg, quint8 data)
{
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 0);
	DriverContext::instance().Configure()->spiWriteByte(CMD_WREG | reg);
	DriverContext::instance().Configure()->spiWriteByte(0x00);
	DriverContext::instance().Configure()->spiWriteByte(data);
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 1);
}

void ads1256::dataReady()
{
	int var;
	for (var = 0; var < 4000000; ++var) {
		if (DriverContext::instance().Configure()->digitalRead(DRDY_PIN) == 0) {
			break;
		}
	}
	if (var >= 4000000) {
		gInfoS() << "Time out 100ms";
	}
//	if (DriverContext::instance().Configure()->digitalRead(DRDY_PIN) != 0) {
//		std::this_thread::sleep_for(std::chrono::milliseconds(10));
//		gInfoS() << "Time out 100ms";
//	}
}

qint8 ads1256::readChipID()
{
	dataReady();
	qint8 id = readData(REG_STATUS);
	gInfoS()<< "read id :"<<(int)id;
	return id >> 4;
}

void ads1256::setChannel(qint8 chnl)
{
	if (chnl > 7) 
		return;
	writeRegister(REG_MUX, (chnl << 4) | (1 << 3));
}

void ads1256::setDiffChannel(qint8 chnl)
{
	if (chnl == 0) {
		writeRegister(REG_MUX, ((0 << 4) | 1)); // DiffChannal  AIN0-AIN1
	} else if (chnl == 1) {
		writeRegister(REG_MUX, ((2 << 4) | 3)); // DiffChannal   AIN2-AIN3
	} else if (chnl == 2) {
		writeRegister(REG_MUX, ((4 << 4) | 5)); // DiffChannal    AIN4-AIN5
	} else if (chnl == 3) {
		writeRegister(REG_MUX, ((6 << 4) | 7)); // DiffChannal   AIN6-AIN7
	}
}

quint8 ads1256::readData(quint8 reg)
{
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 0);
	DriverContext::instance().Configure()->spiWriteByte(CMD_RREG | reg);
	DriverContext::instance().Configure()->spiWriteByte(0x00);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	qint8 data = DriverContext::instance().Configure()->spiReadByte();
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 1);
	return data;
}

void ads1256::configure(quint8 gain, quint8 drate)
{
	dataReady();
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 0);
	DriverContext::instance().Configure()->spiWriteByte(CMD_WREG | 0);
	DriverContext::instance().Configure()->spiWriteByte(0x03);
	DriverContext::instance().Configure()->spiWriteByte((0<<3) | (1<<2) | (0<<1));
	DriverContext::instance().Configure()->spiWriteByte(0x08);
	DriverContext::instance().Configure()->spiWriteByte((0 << 5) | (0 << 3) | (gain << 0));
	DriverContext::instance().Configure()->spiWriteByte(drate);
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 1);
}

quint32 ads1256::readAnalogValue()
{
	dataReady();
	quint8 buffer[3] = {0, 0, 0};
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 0);
	DriverContext::instance().Configure()->spiWriteByte(CMD_RDATA);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	buffer[0] = DriverContext::instance().Configure()->spiReadByte();
	buffer[1] = DriverContext::instance().Configure()->spiReadByte();
	buffer[2] = DriverContext::instance().Configure()->spiReadByte();
	DriverContext::instance().Configure()->digitalWrite(CS_PIN, 1);
	quint32 data = 0;
	data = (buffer[0] << 16) & 0x00FF0000;
	data |= (buffer[1] << 8);
	data |= buffer[2];
	if (data & 0x800000)
		data &= 0xFF000000;
	return data;
}

quint32 ads1256::getChannelValue(qint8 channel)
{
	quint32 value = 0;
	dataReady();
	if (scanMode == 0) {
		if (channel >= 8) {
			return 0;
		}
		setChannel(channel);
		writeCommand(CMD_SYNC);
		writeCommand(CMD_WAKEUP);
		value = readAnalogValue();
	} else {
		if (channel >= 4) {
			return 0;
		}
		setDiffChannel(channel);
		writeCommand(CMD_SYNC);
		writeCommand(CMD_WAKEUP);
		value = readAnalogValue();
	}
	return value;
}

void ads1256::getAll()
{
	for (int var = 0; var < 8; ++var) {
		adcBuffer[var] = getChannelValue(var);
	}
}
