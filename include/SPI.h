// File         : SPI.h
// Version      : 1.0.0
//
// Author       : Michel Schmidt
// E-mail       : schmidtbytes@gmx.de
// Copyright    : (C) SchmidtBytes 2015
//
// Last Changes : 14.04.2015

#ifndef SPI_LIB_H
#define SPI_Lib_H 

#define CS0        RPI_BPLUS_GPIO_J8_24			///< the chip select 0 pin of the SPI
#define CS1        RPI_BPLUS_GPIO_J8_26			///< the chip select 1 pin of the SPI

class SPI
{
private: // variables
	bool running;

public:  // variables

private: // functions

public:  // functions
	SPI();
	~SPI();
	void start();
	void stop();
	uint8_t readWrite(uint8_t *data, uilt32 length, uint8_t cs);
};

#endif // SPI_LIB_H
