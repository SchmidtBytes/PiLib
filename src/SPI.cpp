#include <bcm2835.h>

bool SPI::running = false;
uint32_t SPI::max_freq = MAX_FREQ;

SPI::SPI()
{
	
}

SPI::~SPI()
{

}

int8_t SPI::start(uint32_t freq, uint8_t mode)
{
	int8_t ret;
	mode %= 4;
	if(!running)
	{
		// Init SPI
		bcm2835_init();
		bcm2835_spi_begin();
		ret = setMaxFreq(freq);
		bcm2835_spi_setDataMode(mode);
		bcm2835_spi_setChipSelectPolarity(CS0, LOW);
		bcm2835_spi_setChipSelectPolarity(CS1, LOW);
		running = true;
		return ret;
	}
	else
	{
		bcm2835_spi_setDataMode(mode);
		ret = setMaxFreq(freq);
		if(ret == 0)
			ret = 2;
		else if(ret == -1)
			ret = -2;
		return ret;
	}
}

void SPI::stop()
{
	if(running)
	{
		// close SPI
		bcm2835_spi_end();
		running = false;
		max_freq = MAX_FREQ;
	}
}

int8_t SPI::setMaxFreq(uint32_t freq)
{
	if(freq > max_freq)
		return -1;
	if(freq == max_freq)
		return 0;
	double divider = (((double)MAX_FREQ * 2) / freq) + 0.5;
	bcm2835_spi_setClockDivider((uint16) divider);
	return 1;
}

bool setChipSelect(uint8_t active, uint8_t cs)
{
	if(((active == LOW) || (active == HIGH)) && ((cs == CS0) || (cs == CS1)))
	{
		bcm2835_spi_setChipSelectPolarity(cs, active);
		return true;
	}
	return false;
}

bool SPI::write(uint8_t *data, uint32_t length, uint8_t cs)
{
	if(!running)
	{
		return false;
	}
	if((cs != CS0) && (cs != CS1))
		return;
	bcm2835_spi_chipSelect(cs);
	bcm2835_spi_writenb((char*) data, lebngth);
	return true;
}

bool SPI::readWrite(uint8_t *data, uint32_t length, uint8_t cs)
{
	if(!running)
	{
		return false;
	}
	if((cs != CS0) && (cs != CS1))
		return;
	bcm2835_spi_chipSelect(cs);
	bcm2835_spi_transfern((char*) msg, length);
	return true;
}

bool SPI::readWrite(uint8_t *tx, uint8_t *rx, uint32_t length, uint8_t cs)
{
	if(!running)
	{
		return false;
	}
	if((cs != CS0) && (cs != CS1))
		return;
	bcm2835_spi_chipSelect(cs);
	bcm2835_spi_transfernb ((char*) rx, (char*) tx, data_length);
	return true;
}