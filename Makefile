CFLAGS = -Wall -pedantic -std=c11 -I. -g

all:			test1 test2

integrate.o:	integrate.c integrate.h
				gcc $(CFLAGS) -c integrate.c

test1.o:		test1.c integrate.h
				gcc $(CFLAGS) -c test1.c

test2.o:		test2.c integrate.h
				gcc $(CLFAGS) -c test2.c

test1:			test1.o integrate.o
				gcc $(CLFAGS) test1.o integrate.o -o test1

test2:			test2.o integrate.o
				gcc $(CLFAGS) test2.o integrate.o -o test2

clean:
				rm -f *.o test1 test2
