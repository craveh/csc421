#
# makefile for csc421 (231)
# last-update:
# 	2 sep 2022 -bjr: created
#


C1= stack

all:
	make ${C1}

${C1}: ${C1}.c
	cc -o ${C1} ${C1}.c

test: ${C1}
	./${C1}

clean:
	-rm  ${C1} 

