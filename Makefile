CXX=g++
CXXFLAGS=-std=gnu++11

all: main.o Board.o Point.o
	$(CXX) Board.o Point.o main.o
	./a.out

Board.o: Board.cpp Board.h
	$(CXX) $(CXXFLAGS) -c Board.cpp -o Board.o
	
Point.o: Point.cpp Point.h
	$(CXX) $(CXXFLAGS) -c Point.cpp -o Point.o

main.o: main.cpp Board.h Point.o
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm *.o a.out