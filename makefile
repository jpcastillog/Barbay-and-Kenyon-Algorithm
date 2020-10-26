CFLAGS = -std=c++17 -O
CC = g++

test: barbay_and_kenyon.o search_algorithms.o dip.o
	$(CC) $(CFLAGS) -o test barbay_and_kenyon.o search_algorithms.o dip.o

barbay_and_kenyon.o: barbay_and_kenyon.cpp
	$(CC) $(CFLAGS) -c barbay_and_kenyon.cpp

search_algorithms.o: search_algorithms.cpp
	$(CC) $(CFLAGS) -c search_algorithms.cpp

dip.o: dip.cpp
	$(CC) $(CFLAGS) -c dip.cpp

clean:
	rm -f core *.o test

run:
	./test