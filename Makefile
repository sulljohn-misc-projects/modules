CFLAGS = -Wall -pedantic -std=c11 -I. -g

all:			list_test queue_test

list.o:			list.c list.h
				gcc $(CFLAGS) -c list.c

queue.o:		queue.c queue.h
				gcc $(CFLAGS) -c queue.c

list_test.o:	list_test.c list.h
				gcc $(CFLAGS) -c list_test.c

queue_test.o:	queue_test.c queue.h
				gcc $(CLFAGS) -c queue_test.c

list_test:		list_test.o list.o
				gcc $(CLFAGS) list_test.o list.o -o list_test

queue_test:		queue_test.o queue.o
				gcc $(CLFAGS) queue_test.o queue.o -o queue_test

clean:
				rm -f *.o list queue list_test queue_test
