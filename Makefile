CFLAGS = -Wall -pedantic -std=c11 -I. -g

all:			list_test queue_test hash_test

%.o: %.c %.h
				gcc $(CLAGS) -c $<

list_test:		list_test.o list.o
				gcc $(CLFAGS) list_test.o list.o -o $@

queue_test:		queue_test.o queue.o
				gcc $(CLFAGS) queue_test.o queue.o -o $@

hash_test:		hash_test.o hash.o queue.o
				gcc $(CLFAGS) hash_test.o hash.o queue.o -o $@

clean:
				rm -f *.o list queue hash list_test queue_test hash_test
