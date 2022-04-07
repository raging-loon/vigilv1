all: main clean
CC = gcc
CDEF = -DFUNCTIONALITY_TEST
vwebsrv.o:
	$(CC) -c vwebsrv.c $(CDEF)

main: vwebsrv.o
	gcc -o vwebsrv.exe $^

clean:
	rm *.o
