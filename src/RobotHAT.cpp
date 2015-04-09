#include "RobotHAT.h"



RobotHAT::RobotHAT(RaspberryPi& thePi)
  : pi(thePi)
{
	// Init LED and Buttons
	bcm2835_gpio_fsel(LED,   OUTPUT);
	bcm2835_gpio_fsel(BTN0,  INPUT);
	bcm2835_gpio_fsel(BTN1,  INPUT);

	// Init GPIOs to Inputs
	bcm2835_gpio_fsel(GPIO0, INPUT);
	bcm2835_gpio_fsel(GPIO1, INPUT);
	bcm2835_gpio_fsel(GPIO2, INPUT);
	bcm2835_gpio_fsel(GPIO3, INPUT);
	bcm2835_gpio_fsel(GPIO4, INPUT);
	bcm2835_gpio_fsel(GPIO5, INPUT);
	bcm2835_gpio_fsel(GPIO6, INPUT);
	bcm2835_gpio_fsel(GPIO7, INPUT);
// TODO:	gpio_config = 0x00;

	// Init Motors
	bcm2835_gpio_fsel(MOT1A, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(MOT2A, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(MOT1B, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(MOT2B, BCM2835_GPIO_FSEL_OUTP);
	bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_32);
	bcm2835_pwm_set_mode(0, 1, 1);
	bcm2835_pwm_set_mode(1, 1, 1);
	bcm2835_pwm_set_range(0,255);
	bcm2835_pwm_set_range(1,255);
	bcm2835_pwm_set_data(0,0);
	bcm2835_pwm_set_data(1,0);
	bcm2835_gpio_fsel(PWM0, BCM2835_GPIO_FSEL_ALT0);
	bcm2835_gpio_fsel(PWM1, BCM2835_GPIO_FSEL_ALT0);
	bcm2835_delay(10);
}


RobotHAT::~RobotHAT()
{
	// Motors break
	setMotors(BREAK, BREAK);

	// LED off
	ledOff(0);
// TODO:	ledOff(1);

	// Set GPIOs back to inputs
	bcm2835_gpio_fsel(GPIO0, INPUT);
	bcm2835_gpio_fsel(GPIO1, INPUT);
	bcm2835_gpio_fsel(GPIO2, INPUT);
	bcm2835_gpio_fsel(GPIO3, INPUT);
	bcm2835_gpio_fsel(GPIO4, INPUT);
	bcm2835_gpio_fsel(GPIO5, INPUT);
	bcm2835_gpio_fsel(GPIO6, INPUT);
	bcm2835_gpio_fsel(GPIO7, INPUT);
}





uint8_t RobotHAT::getGpioPin(uint8_t gpio)
{
	switch(gpio)
	{
		case 0:
			return GPIO0;
			break;
		case 1:
			return GPIO1;
			break;
		case 2:
			return GPIO2;
			break;
		case 3:
			return GPIO3;
			break;
		case 4:
			return GPIO4;
			break;
		case 5:
			return GPIO5;
			break;
		case 6:
			return GPIO6;
			break;
		case 7:
			return GPIO7;
			break;
		default:
			return 0xFF;
			break;
	}
}



void RobotHAT::setDigitalDir(uint8_t index, bool direction)
{
  if(index > 7)  return;

  gpio_config &= ~(0x01 << index);
  pi.setGpioDir(getGpioPin(index), direction);
}


bool RobotHAT::digital(uint8_t index)
{
  if (index > 7)  return false;

  pi.getGPIO(getGpioPin(index));
}

bool RobotHAT::setDigital(uint8_t index, bool state)
{
  if(index > 7)  return false;

  if((gpio_config & (0x01 << index)) == 0) return false;
  
  return pi.setGPIO(getGpioPin(index), state);
}



bool RobotHAT::button(uint8_t btn)
{
	switch(btn)
	{
		case 0:
			btn = BTN0;
			break;
		case 1:
			btn = BTN1;
			break;
		default:
			return false;
			break;
	}
	return bcm2835_gpio_lev(btn);
}

void RobotHAT::ledOn(uint8_t index)
{
	bcm2835_gpio_write(LED, ON);
}


void RobotHAT::ledOff(uint8_t index)
{
	bcm2835_gpio_write(LED, OFF);
}


void RobotHAT::toggleLED(uint8_t index)
{
	if(bcm2835_gpio_lev(LED))
		bcm2835_gpio_write(LED, ON);
	else
		bcm2835_gpio_write(LED, OFF);
}



uint16_t RobotHAT::analog(uint8_t input)
{
	uint8_t msg[3] = {0x06, 0x00, 0x00};
	if(input > 7)
		return 65535;
	msg[0] |= input >> 2;
	msg[1] = input << 6;
	pi.spi.readWrite(msg, 3, CS0);
	return ((msg[1] & 0x0F) << 8) + msg[2];
}

float RobotHAT::getVoltage(uint8_t input)
{	
	return (REFVOLTAGE / 4096) * analog(input);
}

uint16_t RobotHAT::diffAnalog(uint8_t input)
{
	uint8_t msg[3] = {0x04, 0x00, 0x00};
	if(input > 7)
		return 65535;
	msg[0] |= input >> 2;
	msg[1] = input << 6;
	pi.spi.readWrite(msg, 3, CS0);
	return ((msg[1] & 0x0F) << 8) + msg[2];
}

float RobotHAT::getDiffVoltage(uint8_t input)
{
	return (REFVOLTAGE / 4096) * diffAnalog(input);
}

void RobotHAT::setMotor(int8_t mot, int16_t speed)
{
	uint8_t pin_mot_1, pin_mot_2;
	if(mot == 0)
	{
		pin_mot_1 = MOT1A;
		pin_mot_2 = MOT2A;
	}
	else if(mot == 1)
	{
		pin_mot_1 = MOT1B;
		pin_mot_2 = MOT2B;
	}
	else
		return;
		
	if(speed == BREAK)
	{
		bcm2835_gpio_write(pin_mot_1, OFF);
		bcm2835_gpio_write(pin_mot_2, OFF);
		bcm2835_pwm_set_data(mot, 255);
		return;
	}
	if(speed < 0)
	{
		bcm2835_gpio_write(pin_mot_1, ON);
		bcm2835_gpio_write(pin_mot_2, OFF);
		speed *= -1;
	}
	else
	{
		bcm2835_gpio_write(pin_mot_1, OFF);
		bcm2835_gpio_write(pin_mot_2, ON);
	}
	if(speed > 255)
		speed = 255;
	bcm2835_pwm_set_data(mot, speed);
}


void RobotHAT::setMotors(int16_t speed0, int16_t speed1)
{
	if(speed0 == BREAK)
	{
		bcm2835_gpio_write(MOT1A, OFF);
		bcm2835_gpio_write(MOT2A, OFF);
		bcm2835_pwm_set_data(0, 255);
	}
	else
	{
		if(speed0 < 0)
		{
			bcm2835_gpio_write(MOT1A, ON);
			bcm2835_gpio_write(MOT2A, OFF);
			speed0 *= -1;
		}
		else
		{
			bcm2835_gpio_write(MOT1A, OFF);
			bcm2835_gpio_write(MOT2A, ON);
		}
		if(speed0 > 255)
			speed0 = 255;
		bcm2835_pwm_set_data(0, speed0);
	}
	if(speed1 == BREAK)
	{
		bcm2835_gpio_write(MOT1B, OFF);
		bcm2835_gpio_write(MOT2B, OFF);
		bcm2835_pwm_set_data(1, 255);
	}
	else
	{
		if(speed1 < 0)
		{
			bcm2835_gpio_write(MOT1B, ON);
			bcm2835_gpio_write(MOT2B, OFF);
			speed1 *= -1;
		}
		else
		{
			bcm2835_gpio_write(MOT1B, OFF);
			bcm2835_gpio_write(MOT2B, ON);
		}
		if(speed1 > 255)
			speed1 = 255;
		bcm2835_pwm_set_data(1, speed1);
	}
}





