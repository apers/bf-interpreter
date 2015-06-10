CC=gcc
CFLAGS=-Wall

all: bf

bf: bf.c bf.h
	$(CC) $(CFLAGS) bf.c bf.h -o bf
clean:
	rm -rf bf
