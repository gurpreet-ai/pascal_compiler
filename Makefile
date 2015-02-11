CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

driver: driver.o scanner.o
	$(CC) driver.o scanner.o -o driver

driver.o: driver.cpp
	$(CC) $(CFLAGS) driver.cpp

scanner.o: scanner.h scanner.cpp
	$(CC) $(CFLAGS) scanner.cpp

clean:
	rm -rf *.o driver