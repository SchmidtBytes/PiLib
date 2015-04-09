// File         : RaspberryPi.h
// Version      : 1.0.0
//
// Author       : Michel Schmidt
// E-mail       : schmidtbytes@gmx.de
// Copyright    : (C) SchmidtBytes 2015
//
// Last Changes : 22.02.2015

#ifndef RASPBERRY_PI_LIB_H
#define RASPBERRY_PI_LIB_H

#include <bcm2835.h>
#include "I2C.h"
#include "SPI.h"

#define INPUT      BCM2835_GPIO_FSEL_INPT		///< the value to set a pin to input
#define OUTPUT     BCM2835_GPIO_FSEL_OUTP		///< the value to set a pin to output


class RaspberryPi
{
private:
	
	static uint8_t active_i2c_client;			///< the currently used i2c client
	
public:
	SPI spi;
	I2C i2c;
	
/// \defgroup init
/// @{
/// @}

public:

/// \defgroup init Initialization Functions
/// @{

	/// \brief Initiates all pins and functions.
  RaspberryPi();
	/// \brief Breaks the motors and deinits the pins.
  ~RaspberryPi();
	
/// @}



/// \defgroup gpio GPIO Functions
/// @{	
	
	/// \brief Sets a GPIO pin to input or output
	/// \param[in] gpio : the GPIO pin to set
	/// \param[in] direction : the direction f the pin
	/// \sa INPUT
	/// \sa OUTPUT
	void setGpioDir(uint8_t gpio, bool direction);
	/// \brief Activates the pull up/down resistor.
	/// For GPIO0 - GPIO6 this is a pull down resistor. For GPIO7 it is a pull up resistor.
	/// \param[in] gpio : the GPIO to set the resistor for
	/// \param[in] res_state : the state of the resistor
	void useRes(uint8_t gpio, bool res_state);
	/// \brief Sets an Output to HIGH or LOW state.
	/// \param[in] gpio : the gpio to set
	/// \param[in] onoff : the state of the gpio
	/// \return returns true for no error
	bool setGPIO(uint8_t gpio, bool onoff);
	/// \brief Returns the state of a pin (also works for outputs)
	/// \param[in] gpio : the gpio to get the state from
	/// \return returns the state of the GPIO0
	/// \return returns false if the GPIO is invalid
	bool getGPIO(uint8_t gpio);
	
/// @}


/// \defgroup i2c I²C access
/// @{
	
	/// \brief Forces the I²C connection to run with 100 kBit/s
	static void forceSlowI2C();
	/// \brief Sends and receives a given amount of bytes
	/// \param[in] slave_addr : the Slave to address
	/// \param[in] send_data : The bytes to send
	/// \param[in] send_length : the amount of bytes to send
	/// \param[in] rec_data : an array to store the received data
	/// \param[in] rec_length : The amount of dara bytes to receive
	/// \return 0x00 if no error occured
	/// \return 0x01 if NACK was received
	/// \return 0x02 for clock timeout
	/// \return 0x04 for an incomplete transmission
	/// \return 0x08 for an invalid slave address
	static uint8_t rwI2C(uint8_t slave_addr, uint8_t* send_data, uint32_t send_length, uint8_t* rec_data, uint32_t rec_length);
	
/// @}

/// \defgroup spi SPI access
/// @{

	/// \brief Sets the maximum frequency for the SPI interface.
	/// Due to the ADC the maximal frequency is 1 MHz.
	/// \param[in] freq : the frequency in Hz. Frequencys greater than 1 MHz are ignored.
	static void setMaxSpiFreq(uint32_t freq);
	/// \brief Sends and receives a certain ammount of bytes via SPI
	/// \param[in,out] data : the data to send; this also holds the received data after the transmission
	/// \param[in] data_length : the amount of bytes to send and receive
	/// \return returns 0x00 if no error occured
	static void rwSPI(uint8_t* data, uint32_t data_length);
	/// \brief Sends and receives a certain ammount of bytes via SPI
	/// \param[in] send_data : the data to send
	/// \param[in] rec_data : holds the received data after the transmission
	/// \param[in] data_length : the amount of bytes to send and receive
	/// \return returns 0x00 if no error occured
	static void rwSPI(uint8_t* send_data, uint8_t* rec_data, uint32_t data_length);

/// @}

/// \defgroup timer Timer Functions
/// @{
	
	/// \brief Waits the given ammount of milliseconds
	/// \param ms : the ammount of milliseconds to wait
	static void milliSleep(uint32_t ms);
	/// \brief Waits the given ammount of microseconds
	/// \param us : the ammount of microseconds to wait
	static void microSleep(uint32_t us);
	
/// @}

};








#endif // RASPBERRY_PI_LIB_H

