/*
 * digitalOutDemo.cpp
 * 
 * Copyright 2015 
 * - Stefan Enderle <enderle@qfix.de>
 * - Michel Schmidt <michel@MiRapi02>
 * 
 */


#include "RaspberryPi.h"
#include "RobotHAT.h"


RaspberryPi pi;       // the main object representing the Raspbery Pi
RobotHAT robot(pi);   // the RobotHAT plugged into the Pi


int main(int argc, char **argv)
{
  robot.setDigitalDir(0, OUTPUT);

  while(true)
    {
      robot.ledOn(0);
      robot.setDigital(0, true);
      pi.msleep(500);       // wait 500ms

      robot.ledOff(0);
      robot.setDigital(0, false);
      pi.msleep(500);       // wait 500ms
    }
}

