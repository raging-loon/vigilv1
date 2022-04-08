all: test clean
CC = gcc
DOPTS = -D LIBTEST
libserialize.o:
	$(CC) -c libserialize.c $(DOPTS) 

test: libserialize.o
	$(CC) -o test.exe $^ $(DOPTS)

clean:
	rm *.o