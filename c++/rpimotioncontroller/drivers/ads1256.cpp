#include "ads1256.h"
#include "3rdparty/debug.h"
#include <thread>

ads1256::ads1256(QObject *parent) : QObject(parent)
{
	init();
}

qint8 ads1256::init()
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
	cfgHangle.digitalWrite(RST_PIN, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	cfgHangle.digitalWrite(RST_PIN, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	cfgHangle.digitalWrite(RST_PIN, 1);
}

void ads1256::setMode(qint8 mode)
{
	
}

void ads1256::writeCommand(qint8 cmd)
{
	cfgHangle.digitalWrite(CS_PIN, 0);
	cfgHangle.spiWriteByte(cmd);
	cfgHangle.digitalWrite(CS_PIN, 1);
}

void ads1256::writeRegister(qint8 reg, qint8 data)
{
	cfgHangle.digitalWrite(CS_PIN, 0);
	cfgHangle.spiWriteByte(CMD_WREG | reg);
	cfgHangle.spiWriteByte(0x00);
	cfgHangle.spiWriteByte(data);
	cfgHangle.digitalWrite(CS_PIN, 1);
}

void ads1256::dataReady()
{
	if (cfgHangle.digitalRead(DRDY_PIN) != 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		gInfoS() << "Time out 100ms";
	}
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

qint8 ads1256::readData(qint8 reg)
{
	cfgHangle.digitalWrite(CS_PIN, 0);
	cfgHangle.spiWriteByte(CMD_RREG | reg);
	cfgHangle.spiWriteByte(0x00);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	qint8 data = cfgHangle.spiReadByte();
	cfgHangle.digitalWrite(CS_PIN, 1);
	return data;
}

void ads1256::configure(qint8 gain, qint8 drate)
{
	dataReady();
	cfgHangle.digitalWrite(CS_PIN, 0);
	cfgHangle.spiWriteByte(CMD_WREG | 0);
	cfgHangle.spiWriteByte(0x03);
	cfgHangle.spiWriteByte((0<<3) | (1<<2) | (0<<1));
	cfgHangle.spiWriteByte(0x08);
	cfgHangle.spiWriteByte((0 << 5) | (0 << 3) | (gain << 0));
	cfgHangle.spiWriteByte(drate);
	cfgHangle.digitalWrite(CS_PIN, 1);
}

qint32 ads1256::readAnalogValue()
{
	dataReady();
	qint8 buffer[3] = {0, 0, 0};
	cfgHangle.digitalWrite(CS_PIN, 0);
	cfgHangle.spiWriteByte(CMD_RDATA);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	buffer[0] = cfgHangle.spiReadByte();
	buffer[1] = cfgHangle.spiReadByte();
	buffer[2] = cfgHangle.spiReadByte();
	cfgHangle.digitalWrite(CS_PIN, 1);
	qint32 data = 0;
	data = ((qint32)buffer[0] << 16) & 0x00FF0000;
	data |= ((qint32)buffer[1] << 8);
	data |= buffer[2];
	if (data & 0x800000)
		data &= 0xFF000000;
	return data;
}

qint32 ads1256::getChannelValue(qint8 channel)
{
	qint32 value = 0;
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
