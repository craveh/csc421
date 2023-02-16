#
# last-update:
#	7 sep 2022 bjr:
#

# uncomment to give demonstrate the assert in a1.c
DEFINES= 
#DEFINES= -DCOUNT=-1

a1: a1.c
	cc -o$@ ${DEFINES}  $<
	./a1
	make clean

clean:
	-rm a1

