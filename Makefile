CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main: main.o scanner.o
	$(CC) main.o scanner.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

scanner.o: scanner.h token.h scanner.cpp
	$(CC) $(CFLAGS) scanner.cpp

clean:
	rm -rf *.o *.gch main