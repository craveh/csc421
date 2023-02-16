#
# oct 16, 2022
# burt rosenberg
# the circ-incl shows what happens with 
#    a circular include. 
# the notok target shows what happens 
#    when an archive is not presented in
#    the correct order
#

ok: a.c b.a
	cc a.c b.a

notok: a.c b.a
	cc b.a a.c

b.a: b.c
	cc -c $<
	ar r b.a b.o
	rm b.o

circ-incl:
	cc circ-incl.c

run:
	./a.out

clean:
	-rm a.o b.a a.out
