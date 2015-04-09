#include <bcm2835.h>

SPI::SPI()
{
	
}

SPI::~SPI()
{
	
}

SPI::start()
{
	if(!running)
	{
	// Init SPI @ 1 MHz
		bcm2835_init();
		bcm2835_spi_begin();
		bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);
		bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
		bcm2835_spi_setChipSelectPolarity(CS0, HIGH);
		running = true;
	}
}

SPI::stop()
{
	if(running)
	{
		// close SPI
		bcm2835_spi_end();
		running = false;
	}
}

uint8_t SPI::readWrite(uint8_t *data, uilt32 length, uint8_t cs)
{
	if((cs != CS0) && (cs != CS1))
		return;
	bcm2835_spi_chipSelect(cs);
	return bcm2835_spi_transfern((char*) msg, length);
}