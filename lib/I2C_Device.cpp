#include "I2C_Device.hpp"
#include <cstddef>

uint8_t I2C_Device::writeMsg(uint8_t* data, uint32_t length)
{
	return BotHat::rwI2C(base_address, data, length, NULL, 0);
}

uint8_t I2C_Device::readMsg(uint8_t* data, uint32_t length)
{
	return BotHat::rwI2C(base_address, NULL, 0, data, length);
}

uint8_t I2C_Device::readWriteMsg(uint8_t* send_data, uint32_t send_length, uint8_t* rec_data, uint32_t rec_length)
{
	return BotHat::rwI2C(base_address, send_data, send_length, rec_data, rec_length);
}

void I2C_Device::force100kBit()
{
	BotHat::forceSlowI2C();
}
