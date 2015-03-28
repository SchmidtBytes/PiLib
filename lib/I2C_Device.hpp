// File         : I2C_Device.hpp
// Version      : 1.0.0
//
// Author       : Michel Schmidt
// E-mail       : schmidtbytes@gmx.de
// Copyright    : (C) SchmidtBytes 2015
//
// Last Changes : 22.02.2015

#ifndef I2C_DEVICE_HPP
#define I2C_DEVICE_HPP

#include "BotHat.hpp"

class I2C_Device
{
	protected:
	uint8_t base_address;
	
	uint8_t writeMsg(uint8_t* data, uint32_t length);
	uint8_t readMsg(uint8_t* data, uint32_t length);
	uint8_t readWriteMsg(uint8_t* send_data, uint32_t send_length, uint8_t* rec_data, uint32_t rec_length);
	void force100kBit();
	
	public:
};

#endif // I2C_DEVICE_HPP
