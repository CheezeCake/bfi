CC=cc
CFLAGS=-std=c89 -Wall -pedantic

all: bfi

bfi: bfi.o
	$(CC) bfi.o -o bfi

bfi.o: bfi.c
	$(CC) -c bfi.c -o bfi.o $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -f bfi.o

mrproper: clean
	rm -f bfi
