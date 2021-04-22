#ifndef CONFIG_H
#define CONFIG_H

#define RST_PIN	   18
#define CS_PIN	   22
#define CS_DAC_PIN 23
#define DRDY_PIN   17

class config
{
public:
	config();
	void digitalWrite(int pin, int value);
	int digitalRead(int pin);
	int spiWriteByte(uint8_t data);
	uint8_t spiReadByte();
};

#endif // CONFIG_H