#include <bcm2835.h>

I2C::I2C()
{
	running = false;
}

I2C::~I2C()
{
	
}

I2C::start()
{
	if(!running)
	{
		// Init I2C @ 400 KHz
		bcm2835_i2c_begin();
		bcm2835_i2c_set_baudrate(400000);
		running = true;
	}
}

I2C::stop()
{
	if(running)
	{
        // close i2c
		bcm2835_i2c_end();
		running = true;
	}
}