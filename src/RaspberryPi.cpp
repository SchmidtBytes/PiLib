#include "RaspberryPi.h"

#include <unistd.h>


#define SPI_CS1        RPI_BPLUS_GPIO_J8_26			///< the chip select 1 pin of the SPI



uint8_t RaspberryPi::active_i2c_client = 0xFF;





RaspberryPi::RaspberryPi()
{
	// Init GPIO module
	if (!bcm2835_init())
	{
		throw INIT_EXEPTION;
		/* TODO: ERROR */
	}

	// Init I2C @ 400 KHz
	bcm2835_i2c_begin();
	bcm2835_i2c_set_baudrate(400000);
}




RaspberryPi::~RaspberryPi()
{
        // close i2c
	bcm2835_i2c_end();

	// Deinit GPIO module
	bcm2835_close();
}

void RaspberryPi::setGpioDir(uint8_t pin, bool direction)
{
	if(direction == INPUT)
	{
		bcm2835_gpio_fsel(pin,  BCM2835_GPIO_FSEL_INPT);
	}
	else
	{
		bcm2835_gpio_fsel(pin,  BCM2835_GPIO_FSEL_OUTP);
	}
}

void RaspberryPi::useRes(uint8_t pin, bool res_state)
{
	uint8_t pud = BCM2835_GPIO_PUD_OFF;
	
	if(res_state)
	{
		if(pin == 7)
			pud = BCM2835_GPIO_PUD_UP;
		else
			pud = BCM2835_GPIO_PUD_DOWN;
	}
	bcm2835_gpio_set_pud(pin, pud);
}


bool RaspberryPi::setGPIO(uint8_t pin, bool onoff)
{
	bcm2835_gpio_write(pin, onoff);
	return true;   // TODO:  some error handling possible?
}


bool RaspberryPi::getGPIO(uint8_t pin)
{
	return bcm2835_gpio_lev(pin);
}

bool RaspberryPi::startI2C()
{
	//TODO
}

void RaspberryPi::forceSlowI2C()
{
	bcm2835_i2c_set_baudrate(100000);
}

uint8_t RaspberryPi::rwI2C(uint8_t slave_addr, uint8_t* send_data, uint32_t send_length, uint8_t* rec_data, uint32_t rec_length)
{	
	if(slave_addr > 0x7F)
		return 0x08;
	if(slave_addr != active_i2c_client)
		bcm2835_i2c_setSlaveAddress(slave_addr);
	
	if((send_length == 0) && (rec_length == 0))
	{
		return 0x00;
	}
	else if(rec_length == 0)
	{
		return bcm2835_i2c_write((char*) send_data, send_length);
	}
	else if(send_length == 0)
	{
		return bcm2835_i2c_read((char*) rec_data, rec_length);
	}
	return bcm2835_i2c_write_read_rs((char*) send_data, send_length, (char*) rec_data, rec_length);
}

void RaspberryPi::setMaxSpiFreq(uint32_t freq)
{
	float f = 250000000.0;
	
	if(freq > 1000000)
	{
		return;
	}
	
	f = (f / freq) + 0.5;
	freq = f;
	bcm2835_spi_setClockDivider(freq);
}

void RaspberryPi::rwSPI(uint8_t* data, uint32_t data_length)
{
	bcm2835_spi_chipSelect(SPI_CS1);
	bcm2835_spi_transfern((char*) data, data_length);
}

void RaspberryPi::rwSPI(uint8_t* send_data, uint8_t* rec_data, uint32_t data_length)
{
	bcm2835_spi_chipSelect(SPI_CS1);
	bcm2835_spi_transfernb ((char*) send_data, (char*) rec_data, data_length);
}

void RaspberryPi::milliSleep(uint32_t ms)
{
	usleep(ms * 1000);
}

void RaspberryPi::microSleep(uint32_t us)
{
	usleep(us);
}
