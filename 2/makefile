CC=g++
CFLAGS=-pedantic -Wall -std=c++17 -Wextra -Wno-unused-variable

all: go

go: Main.o treeMain.o
	$(CC) $(CFLAGS) Main.o treeMain.o

Main.o: Main.cpp
	$(CC) -c Main.cpp

treeMain.o: treeMain.cpp
	$(CC) -c treeMain.cpp

clean:
	rm -rf *.o *.gch a.out HardTest.txt
