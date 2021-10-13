FLAGS= -g -pedantic -Wall -std=c++17 -Werror -Wno-sign-compare -O2 -lm

all: main ll
	g++ $(FLAGS) ./src/main.o ./src/ll.o -o solution

main: ./src/main.cpp ./src/ll.hpp
	g++ $(FLAGS) -c ./src/main.cpp -o ./src/main.o

ll: ./src/ll.cpp ./src/ll.hpp
	g++ $(FLAGS) -c ./src/ll.cpp -o ./src/ll.o

clean:
	rm -rf solution ./src/*.o
