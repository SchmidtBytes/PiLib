
INCLUDES += -I../include
TARGET    = ../lib/libpilib.a


all: RaspberryPi.o RobotHAT.o
	ar rcs libpilib.a RaspberryPi.o RobotHAT.o
	mv libpilib.a ${TARGET}

RobotHAT.o: RobotHAT.cpp
	g++ ${INCLUDES} -c RobotHAT.cpp

RaspberryPi.o: RaspberryPi.cpp
	g++ ${INCLUDES} -c RaspberryPi.cpp

# alle Dateien aufräumen
clean:
	rm -rf *o *~ 

distclean:
	rm -rf *o *~ ${TARGET}
