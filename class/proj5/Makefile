#
# Makefile for project5 csc421.231
# last-update:
# 	28 nov 2022 -bjr:
#    5 dec 2022 -bjr: test case
#

V=
# comment out for not verbose
V= -vv 

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m

F= skeleton-key
G= skeleton-key-util

$F: $F.c $G.o $F.h
	cc -o $@ $< $G.o
	
$G.o: $G.c $F.h
	cc -c $< 

run: $F
	./$< $V

test: $F
	@echo "${RED}testing ... ${NC}"
	cat test1.run | ./$F > test.out
	diff test1.ref test.out
	@echo "*** ${GREEN}PASSED the test ${NC}***"


sample-1: $F
	@echo "${RED}>>> (should print)\n${GREEN}a: hello\nb: world\n${RED}<<<${NC}"
	echo "wr a hello\nwr b world\nrd a\nrd b" | ./$F
	
sample-2: $F
	@echo "${RED}>>> (should print)\n${GREEN}a: hello\nb: december\n${RED}<<<${NC}"
	echo "wr b world\nwr a hello\nwr b december\nrd a\nrd b" | ./$F
	
sample-3: $F
	@echo "${RED}>>> (should print)\n${GREEN}saying: the-quick-brown-fox-jumped-over-the-lazy-dog\n${RED}<<<${NC}"
	echo "wr saying the-quick-brown-fox-jumped-over-the-lazy-dog\nrd saying" | ./$F

clean:
	-rm $F $G.o test.out
