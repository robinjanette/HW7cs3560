all: build
build: checkers.out
checkers.out: checkers_pieces.o checkers.o piece.o main.o
	g++ -g -Wall *.o -o checkers.out
main.o: main.cc
	g++ -g -Wall -c main.cc
%.o: %.cc %.h
	g++ -g -Wall -c $<
clean: 
	rm -f *.o core *.out
