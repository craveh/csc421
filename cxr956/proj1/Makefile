#
# Makefile for pipe-test, csc421.231
#
# last-update:
# 	4 sep 2022 -bjr:
#

F= my-word-count
FILENAME= $F.h
# TEST_FILENAME = $F.h
TEST_FILENAME = test-file.txt
VERBOSE= -v
#OPTIONS=
OPTIONS= -lm

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

my-tests: $F
	@echo "TEST 1: -c\n"
	./$F ${VERBOSE} -c ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 2: -w\n"
	./$F ${VERBOSE} -w ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 3: no flag\n"
	./$F ${VERBOSE} ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 4: -m\n"
	./$F ${VERBOSE} -m ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 5: -c -l\n"
	./$F ${VERBOSE} -c -l ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 6: -w -w\n"
	./$F ${VERBOSE} -w -w ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 7: -ww\n"
	./$F ${VERBOSE} -ww ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 8: -w -l\n"
	./$F ${VERBOSE} -w -l ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 9: -ml -l\n"
	./$F ${VERBOSE} -ml ${TEST_FILENAME} > $F.out
	cat $F.out
	@echo "\nTEST 10: -l -l\n"
	./$F ${VERBOSE} -l ${TEST_FILENAME} > $F.out
	cat $F.out


# this target is really for the professor to run, to create the ref files
ref: $F
	@echo "***\n*** ${RED}beware: this is to be run only on a correct program${NC}\n***"
	./$F ${OPTIONS} ${FILENAME} > $F${OPTIONS}.ref

clean:
	-rm $F $F.out

