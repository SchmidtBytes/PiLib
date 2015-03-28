/*
 * unbenannt.cxx
 * 
 * Copyright 2015
 *   Michel Schmidt <schmidtbytes@gmx.de>
 * 
 */


#include "RaspberryPi.h"
#include "RobotHAT.h"


RaspberryPi pi;
RobotHAT robot(pi);


int main(int argc, char **argv)
{
  while(true)
    {
      robot.ledOn(0);
      pi.msleep(500);       // wait 500ms

      robot.ledOff(0);
      pi.msleep(500);       // wait 500ms
    }
}

