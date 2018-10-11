CFLAGS = -Wall -pedantic -std=c11 -I../test -I../src -g

GCC = gcc
XFLAGS =  -g --coverage

all:			list_test queue_test hash_test

# make the object codes for the modules
%.o:  ../src/%.c ../src/%.h
			$(GCC) $(CFLAGS) $(XFLAGS) -c $<

# make the object codes for the tests
list_test.o:	../test/list_test.c
						$(GCC) $(CFLAGS) $(XFLAGS) -c $<

queue_test.o:	../test/queue_test.c
						$(GCC) $(CFLAGS) $(XFLAGS) -c $<

hash_test.o:	../test/hash_test.c
						$(GCC) $(CFLAGS) $(XFLAGS) -c $<

# make the executables 
list_test:	list_test.o list.o
						$(GCC) $(CFLAGS) $(XFLAGS) list_test.o list.o -o $@

queue_test:	queue_test.o queue.o
						$(GCC) $(CFLAGS) $(XFLAGS) queue_test.o queue.o -o $@ 

hash_test:	hash_test.o hash.o queue.o
						$(GCC) $(CFLAGS) $(XFLAGS) hash_test.o hash.o queue.o -o $@

gcov: list_test queue_test hash_test
			mod3.test
			gcov hash.c
			gcov queue.c
			gcov list.c

clean:
				rm -f *.o list_test queue_test hash_test

# run all the tests
tests:
				mod3.test
