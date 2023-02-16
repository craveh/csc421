#
# last-update:
#	20 oct 2022 -bjr: new
#

O= -v
# an option string to crash riddle2
CRASH_OPTIONS= 

all:
	make clean
	make run

riddle1: riddle1.c
	cc -o $@ $<

riddle2: riddle2.c
	cc -o $@ $<

run: riddle1 riddle2
	./riddle1
	./riddle2 $O

crash: riddle2
	./riddle2 ${CRASH_OPTIONS}

clean:
	-rm riddle1 riddle2

