/*
 * motorDemo.cpp
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
  while(true)
    {
      if (robot.button(0) || robot.button(1)) {
        robot.setMotor(0,100);
        robot.setMotor(1,100);
      }
      else {
        robot.setMotor(0,0);
        robot.setMotor(1,0);
      }
    }
}

