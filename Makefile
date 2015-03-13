CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main: main.cpp scanner.o
	$(CC) main.cpp -o main

scanner.o : scanner.cpp token.h
	$(CC) -c scanner.cpp

clean:
	rm -rf *.o main