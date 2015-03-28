
DEMO = digitalOutDemo

INCLUDES += -I../../include
LIBS     += -L../../lib -lpilib -lbcm2835 
TARGET    = ../../bin/${DEMO}

#Link all
${DEMO}: ${DEMO}.o 
	g++ ${INCLUDES} -o ${DEMO} ${DEMO}.o ${LIBS}
	mv ${DEMO} ${TARGET}

#compile main file
${DEMO}.o: ${DEMO}.cpp
	g++ ${INCLUDES} -c ${DEMO}.cpp

# clean (and leave binaries OK)
clean:
	rm -rf *o *~ 

# clean all (back to distribution level)
distclean:
	rm -rf *o *~ ${TARGET}

