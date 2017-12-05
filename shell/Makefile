all: myShell

mytoc.o: mytoc.c
	cc -c mytoc.c
myShell: myShell.o mytoc.o
	cc -o myShell myShell.o mytoc.o
myShell.o: myShell.c mytoc.h
	cc -c myShell.c

clean:
	rm *o myShell
 
