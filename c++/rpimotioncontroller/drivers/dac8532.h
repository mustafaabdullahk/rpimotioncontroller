#ifndef DAC8532_H
#define DAC8532_H

#define channel_A	  0x30
#define channel_B	  0x34
#define DAC_Value_MAX 65535
#define DAC_VREF	  3.3

#include <QObject>


class dac8532 : public QObject
{
	Q_OBJECT
public:
	explicit dac8532(QObject *parent = nullptr);
	static void configModule(uint8_t channel, uint16_t data);
	void outVoltage(uint8_t channel, float voltage);
	
signals:
	
public slots:
};

#endif // DAC8532_H