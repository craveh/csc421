#
# Makefile for pipe-test, csc421.231
#
# last-update:
# 	4 sep 2022 -bjr:
#

F= my-word-count
FILENAME= $F.h
VERBOSE= -v
OPTIONS=
#OPTIONS= -lm

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m


all:
	make $F

$F: $F.c $F.h
	cc -o $@ $< 

run: $F
	./$F ${VERBOSE} ${OPTIONS} ${FILENAME}

test: $F
	./$F ${VERBOSE} ${OPTIONS} ${FILENAME} > $F.out
	cat $F.out
	diff $F${OPTIONS}.ref $F.out
	@echo "***\n*** ${GREEN}passed the basic test${NC}\n***"

# this target is really for the professor to run, to create the ref files
ref: $F
	@echo "***\n*** ${RED}beware: this is to be run only on a correct program${NC}\n***"
	./$F ${OPTIONS} ${FILENAME} > $F${OPTIONS}.ref

clean:
	-rm $F $F.out

