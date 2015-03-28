

all: doxygen.conf
	doxygen Doxyfile

clean:
	rm -f *~

distclean:
	rm -f *~ -r html latex

install:
	cp -R html /var/www/pilib
