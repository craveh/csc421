#
# makefile for csc421 (231)
# last-update:
# 	2 sep 2022 -bjr: created
#


C1= f1
C2= f2



all:
	echo ${C1}
	make clean
	make ${C1}
	make ${C2}

${C1}:
	cc -o ${C1} ${C1}.c

${C2}:
	cc -o ${C2} ${C2}.c

ps:
	ps -jHf -Uubuntu

clean:
	-rm  ${C1} ${C2}

