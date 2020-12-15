CFLAGS = -std=c++17 -O
CC = g++

test: main.o barbay_and_kenyon.o search_algorithms.o dip.o load_tupples.o
	$(CC) $(CFLAGS) -o test main.o barbay_and_kenyon.o search_algorithms.o dip.o load_tupples.o

barbay_and_kenyon.o: barbay_and_kenyon.cpp
	$(CC) $(CFLAGS) -c barbay_and_kenyon.cpp

search_algorithms.o: search_algorithms.cpp
	$(CC) $(CFLAGS) -c search_algorithms.cpp

dip.o: dip.cpp
	$(CC) $(CFLAGS) -c dip.cpp

load_tupples.o: load_tupples.cpp
	$(CC) $(CFLAGS) -c load_tupples.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f core *.o test

run:
	./test