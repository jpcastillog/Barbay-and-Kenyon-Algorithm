CFLAGS = -O
CC = g++

test: barbay_and_kenyon.o search_algorithms.o
	$(CC) $(CFLAGS) -o test barbay_and_kenyon.o search_algorithms.o

barbay_and_kenyon.o: barbay_and_kenyon.cpp
	$(CC) $(CFLAGS) -c barbay_and_kenyon.cpp

search_algorithms.o: search_algorithms.cpp
	$(CC) $(CFLAGS) -c search_algorithms.cpp

clean:
	rm -f core *.o 