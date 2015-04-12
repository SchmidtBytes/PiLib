// File         : I2C.h
// Version      : 1.0.0
//
// Author       : Michel Schmidt
// E-mail       : schmidtbytes@gmx.de
// Copyright    : (C) SchmidtBytes 2015
//
// Last Changes : 11.04.2015

#ifndef I2C_LIB_H
#define I2C_Lib_H 

class I2C
{
private: // variables
	bool running;
	
public:  // variables

private: // functions

public:  // functions
	I2C();
	~I2C();
	void start();
	void stop();
};

#endif // I2C_LIB_H
