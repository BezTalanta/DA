CC=g++
CFLAGS=-std=c++17 -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic

all: go

go: DA4.o BM.o
	$(CC) $(CFLAGS) DA4.o BM.o -o solution

DA4.o: DA4.cpp BM.hpp
	$(CC) $(CFLAGS) -c DA4.cpp

BM.o: BM.cpp BM.hpp
	$(CC) $(CFLAGS) -c BM.cpp

clean:
	rm -rf *.o *.gch solution
