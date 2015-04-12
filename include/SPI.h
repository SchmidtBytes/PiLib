// File         : SPI.h
// Version      : 1.0.0
//
// Author       : Michel Schmidt
// E-mail       : schmidtbytes@gmx.de
// Copyright    : (C) SchmidtBytes 2015
//
// Last Changes : 11.04.2015

#ifndef SPI_LIB_H
#define SPI_Lib_H 

#define CS0          RPI_BPLUS_GPIO_J8_24		///< the chip select 0 pin of the SPI
#define CS1          RPI_BPLUS_GPIO_J8_26		///< the chip select 1 pin of the SPI

#define KHz          (* 1000)					///< Factor for Kilohertz
#define MHz          (* 1000 KHz)				///< Factor for Megahertz
#define MAX_FREQ     125 MHz					///< Maximal frequency for the SPI (125 MHz)

/// \brief SPI Data modes
typedef enum
{
    MODE0 = 0,  ///< CPOL = 0, CPHA = 0
    MODE1 = 1,  ///< CPOL = 0, CPHA = 1
    MODE2 = 2,  ///< CPOL = 1, CPHA = 0
    MODE3 = 3,  ///< CPOL = 1, CPHA = 1
}SPIModes;

class SPI
{
private: // variables
	static bool running;						///< indicates if the SPI module is running or not
	static uint32_t max_freq;					///< the maximal speed for the slowest device

public:  // variables

private: // functions

public:  // functions
	/// \brief sets up the SPI class
	SPI();
	/// \brief destroys the SPI class
	~SPI();
	/// \brief Starts the SPI communication
	/// Starts the SPI Communication in the given mode and the given frequency.
	/// Chip select Signals are active low by default.
	/// Change the default by using setChioSelect()
	/// \param[in] freq : the frequency to set. Default is 125 MHz. Examples: 1MHz; 1000KHz; 1000000
	/// \param[in] mode : the SPI mode to use. The modes are stored in SPIModes. Default is MODE0.
	/// \return  0 : SPI started and freq matches maximum frequency
	/// \return -2 : SPI already running and freq greater than the set maximum frequency
	/// \return -1 : freq greater than MAX_FREQ
	/// \return  1 : SPI Started and freq set as maximal frequency
	/// \return  2 : SPI already running; maximal frequency set to freq
	int8_t start(uint32_t freq = MAX_FREQ, uint8_t mode = MODE0);
	/// \brief Stops the SPI communication (if running)
	void stop();
	/// \brief Sets the maximal frequency
	/// Only sets the maximum frequency if the maximum frequency set before is greater
	/// \param[in] freq : the frequency to set. Examples: 1MHz; 1000KHz; 1000000
	/// return -1 : freq greater than currently set maximum frequency
	/// return  0 : freq matches currently set maximum frequency
	/// return  1 : freq set as maximum frequency
	int8_t setMaxFreq(uint32_t freq);
	/// \brief Sets the active state for one of the chip select signals
	/// \patam[in] active : The active state of the chip select signal; use HIGH and LOW
	/// \param[in] cs : The chip select to set; use CS0 and CS1
	/// \return true if all input values are valid
	/// \return false if at least one of the values is not valid
	bool setChipSelect(uint8_t active, uint8_t cs);
	/// \brief Writes a certain amount of bytes via SPI
	/// \param[in] data : The data to send
	/// \param[in] length : The amount of data bytes to send
	/// \param[in] cs : The chip select to use; use CS0 and CS1
	/// \return true if SPI is active; false if not
	bool write(uint8_t *data, uint32_t length, uint8_t cs);
	/// \brief Writes and reads a certain amount of bytes via SPI
	/// \param[in,out] data : The data to send. This stores the received data after transmitting
	/// \param[in] length : The amount of data bytes to send and receive
	/// \param[in] cs : The chip select to use; use CS0 and CS1
	/// \return true if SPI is active; false if not
	bool readWrite(uint8_t *data, uint32_t length, uint8_t cs);
	/// \brief Writes and reads a certain amount of bytes via SPI
	/// \param[in] tx : The data to send
	/// \param[out] rx : The received data
	/// \param[in] length : The amount of data bytes to send and receive
	/// \param[in] cs : The chip select to use; use CS0 and CS1
	/// \return true if SPI is active; false if not
	bool readWrite(uint8_t *tx, uint8_t *rx, uint32_t length, uint8_t cs);
};

#endif // SPI_LIB_H
