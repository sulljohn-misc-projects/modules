all:
			(cd build; make)

tests:
			(cd build; make tests)

gcov:
			(cd ./build; make gcov)

gprof:
			(cd ./build; make clean; make gprof XFLAGS='-pg -O'; make clean)

clean:
			(cd ./build; make clean)