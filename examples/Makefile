DIRS = ledDemo buttonDemo digitalOutDemo motorDemo


all:
	for dir in $(DIRS); do make -s -w -C $$dir; done

clean:
	for dir in $(DIRS); do make -s -w -C $$dir clean; done
	rm -f *~ 

distclean:
	for dir in $(DIRS); do make -s -w -C $$dir distclean; done
	rm -f *~ 
