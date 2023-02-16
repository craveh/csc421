#
# Makefile for proj3 csc421.231
# last-update:
# 	16 oct2022 -bjr:
#

V=
# comment out for not verbose
#V= -v
#OPTS= -k4
N= 5

F= smurf
G= smurf-util

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m

$F: $F.c $G.o $F.h
	cc -o $@ $< $G.o -lpthread 


$G.o: $G.c $F.h
	cc -c $<
	
run: $F
	./$< $V $N

test: $F
	@echo "***\n*** ${RED}testing (will take a minute) ...${NC}\n***"
	./$< $V 5 > $F.out 
	cat $F.out
	diff $F.out $F.ref
	@echo "***\n*** ${GREEN}passed the basic test${NC}\n***"

clean:
	-rm $F $G.o $F.out
