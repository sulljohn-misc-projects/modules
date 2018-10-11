CFLAGS = -Wall -pedantic -std=c11 -I../test -I../src -g

GCC = gcc

all:			list_test queue_test hash_test

# make the object codes for the modules
%.o:  ../src/%.c ../src/%.h
			$(GCC) $(CFLAGS) -c $<

# make the object codes for the tests
list_test.o:	../test/list_test.c
						$(GCC) $(CFLAGS) -c $<

queue_test.o:	../test/queue_test.c
						$(GCC) $(CFLAGS) -c $<

hash_test.o:	../test/hash_test.c
						$(GCC) $(CFLAGS) -c $<

# make the executables 
list_test:	list_test.o list.o
						$(GCC) $(CFLAGS) list_test.o list.o -o $@

queue_test:	queue_test.o queue.o
						$(GCC) $(CFLAGS) queue_test.o queue.o -o $@ 

hash_test:	hash_test.o hash.o queue.o
						$(GCC) $(CFLAGS) hash_test.o hash.o queue.o -o $@

clean:
				rm -f *.o list_test queue_test hash_test

# run all the tests
tests:
				mod3.test
