DIRS = src examples doc

all:
	for dir in $(DIRS); do make -s -w -C $$dir; done

clean:
	for dir in $(DIRS); do make -s -w -C $$dir clean; done

distclean:
	for dir in $(DIRS); do make -s -w -C $$dir distclean; done

