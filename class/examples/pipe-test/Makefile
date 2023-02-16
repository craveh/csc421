#
# Makefile for pipe-test, csc421.231
#
# last-update:
# 	4 sep 2022 -bjr:
#

F= pipe-test
FILENAME= $F
VERBOSE= -v

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m


all:
	make $F

$F: $F.c $F.h
	cc -o $@ $< 

run: $F
	./$F ${VERBOSE}

test: $F
	./$F > $F.out
	cat $F.out
	diff $F.ref $F.out
	@echo "***\n*** ${GREEN}passed the basic test${NC}\n***"

clean:
	-rm $F $F.out

