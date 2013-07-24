.PHONY  = clean dist
SUBDIRS = ./lib ./src

all:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

clean: distclean
	for dir in $(SUBDIRS); do $(MAKE) -s -C $$dir clean; done

dist: clean
	(cd ..; tar cfz spaceship.tgz spaceship; mv spaceship.tgz spaceship)

distclean:
	-$(RM) *.tgz
