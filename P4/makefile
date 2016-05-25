debug: main.cpp  Heash.cpp
	g++ -g -ansi -pedantic -Wall -Werror -std=c++11 main.cpp  Heash.cpp -o debug
all : main.o  Heash.o
	g++ -ansi -pedantic -Wall -Werror -std=c++11 main.o  Heash.o -o main
main.o: main.cpp
	g++ -c -ansi -pedantic -Wall -Werror -std=c++11 main.cpp
Heap.o: Heap.h Heap.cpp
	g++ -c -ansi -pedantic -Wall -Werror -std=c++11 Heap.cpp
Hash.o: Hash.h Hash.cpp
	g++ -c -ansi -pedantic -Wall -Werror -std=c++11 Hash.cpp
Heash.o: Heash.h Heash.cpp 
	g++ -c -ansi -pedantic -Wall -Werror -std=c++11 Heash.cpp

clean: 
	rm -f debug
	rm -f main
	rm -f *.o
