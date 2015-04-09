// File         : BotHat.h
// Version      : 1.0.0
//
// Author       : Michel Schmidt
// E-mail       : schmidtbytes@gmx.de
// Copyright    : (C) SchmidtBytes 2015
//
// Last Changes : 22.02.2015

/// \mainpage C++ library for the BotHat extension of the Raspberry Pi
///
/// \version 1.0.0 Basic functionality for the accelleration sensor variant
///
/// \date 22.Feb.2015
/// \author Michel Schmidt (SchmidtBytes@gmx.de)

#ifndef ROBOT_HAT_LIB_H
#define ROBOT_HAT_LIB_H 

#include "RaspberryPi.h"


#define LED        RPI_BPLUS_GPIO_J8_31			///< the pin of the LED
#define BTN0       RPI_BPLUS_GPIO_J8_29			///< the pin of the first button
#define BTN1       RPI_BPLUS_GPIO_J8_40			///< the pin of the second button
#define GPIO0      RPI_BPLUS_GPIO_J8_11			///< the GPIO1 pin
#define GPIO1      RPI_BPLUS_GPIO_J8_12			///< the GPIO2 pin
#define GPIO2      RPI_BPLUS_GPIO_J8_13			///< the GPIO3 pin
#define GPIO3      RPI_BPLUS_GPIO_J8_15			///< the GPIO4 pin
#define GPIO4      RPI_BPLUS_GPIO_J8_16			///< the GPIO5 pin
#define GPIO5      RPI_BPLUS_GPIO_J8_18			///< the GPIO6 pin
#define GPIO6      RPI_BPLUS_GPIO_J8_22			///< the GPIO7 pin
#define GPIO7      RPI_BPLUS_GPIO_J8_07			///< the GPIO8 pin
#define MOT1A      RPI_BPLUS_GPIO_J8_37			///< 1st direction pin for motor A
#define MOT2A      RPI_BPLUS_GPIO_J8_38			///< 2nd direction pin for motor A
#define MOT1B      RPI_BPLUS_GPIO_J8_35			///< 1st direction pin for motor B
#define MOT2B      RPI_BPLUS_GPIO_J8_36			///< 2nd direction pin for motor B
#define PWM0       RPI_BPLUS_GPIO_J8_32			///< PWM pin for motor A
#define PWM1       RPI_BPLUS_GPIO_J8_33			///< PWM pin for motor B

/// \defgroup constants Constants for the BotHat
/// Some Values for a more comfortable use of the BotHat Functions
/// @{

#define OFF        0							///< turns the LED, a GPIO or a motor off
#define ON         1							///< turns the LED or a GPIO ON
#define BREAK      -32768						///< actively breaks a motor

#define REFVOLTAGE 3.3							///< the reference voltage for the analog inputs

/// @}

class RobotHAT
{
  RaspberryPi& pi;

  uint8_t gpio_config;						///< saves which GPIO pins are inputs and which are outputs


/// \defgroup gpio
/// @{
	
	/// \brief returns the adress for the GPIO pins
	/// \param[in] gpio : the gpio pin to use
	/// \return returns the address of the GPIO pin
	/// \returns 0xFF for an invalid GPIO pin
	uint8_t getGpioPin(uint8_t gpio);
	
/// @}
	

// RobotHAT() : pi()  {} 


public:
	
/// \defgroup init Initialization Functions
/// @{

	/// \brief Initiates all pins and functions.
	RobotHAT(RaspberryPi& thePi);
	/// \brief Breaks the motors and deinits the pins.
	~RobotHAT();
	
/// @}


        void setDigitalDir(uint8_t index, bool direction);

	bool digital(uint8_t index);
        bool setDigital(uint8_t index, bool state);

	
/// \defgroup btn Button and LED
/// @{

	/// \brief Returns the current state of a button.
	/// \param[in] btn : the requested button (0 or 1)
	/// \return true if the button us presessed; false if not
	/// \return false if the requested button does not exist
	bool button(uint8_t btn);
	/// \brief Turns a LED on
	/// \param[in] index : index of the desired LED 
	void ledOn(uint8_t index=0);
	/// \brief Turns a LED off
	/// \param[in] index : index of the desired LED 
	void ledOff(uint8_t index=0);
	/// \brief Toggles the LED
	/// \param[in] index : index of the desired LED 
	void toggleLED(uint8_t index=0);

/// @}
	

/// \defgroup analog Analog inputs
/// @{

	/// \brief Reads the requested analog input
	/// \param[in] input : the selected input
	/// \return returns the 12 bit value of this input
	/// \return returns 65535 if this input does not exist
	/// \sa getVoltage()
	uint16_t analog(uint8_t input);
	/// \brief Returns the Voltage of an analog input
	/// \param[in] input : the selected input
	/// \return returns a value between 0 ans 3.3 Volts
	/// \return returns a value below -10 if this input does not exist
	/// \sa Analog()
	float getVoltage(uint8_t input);
	/// \brief Makes a differential measurement between two Inputs.
	/// The differental inputs are 0 and 1, 2 and 3, 4 and 5, 6 and 7.
	/// \param[in] input : the selected input (does not matter which of the two inputs is given)
	/// \return returns the resulting 12 bit value of the measurement
	/// \return returns 65535 if this input does not exist
	/// \sa getDiffVoltage()
	uint16_t diffAnalog(uint8_t input);
	/// \brief Makes a differential measurement between two Inputs and returns the result as Voltage
	/// The differental inputs are 0 and 1, 2 and 3, 4 and 5, 6 and 7.
	/// \param[in] input : the selected input (does not matter which of the two inputs is given)
	/// \return returns a the value of the differential measurement
	/// \return returns a value below -10 if this input does not exist
	/// \sa diffAnalog()
	float getDiffVoltage(uint8_t input);
	
/// @}

/// \defgroup motor Motor Functions
/// @{

	/// \brief Sets the speed for one Motor
	/// \param[in] mot : the motor to set
	/// \param[in] speed : the speed for the motor (-255 to 255, OFF or Break are valid. Too big values result in maximal speed)
	void setMotor(int8_t mot, int16_t speed);
	/// \brief Sets the speed for both Motors
	/// \param[in] speed0 : the speed for motor0
	/// \param[in] speed1 : the speed for motor1
	void setMotors(int16_t speed0, int16_t speed1);
	
/// @}
	

};

#endif // ROBOT_HAT_LIB_H
