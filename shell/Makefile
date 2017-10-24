all: test

mytoc.o: mytoc.c
	cc -c mytoc.c
test: test.o mytoc.o
	cc -o test test.o mytoc.o
test.o: test.c mytoc.h
	cc -c test.c
clean:
	rm *o test
 
