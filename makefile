all: AStarTest

AStarTest: Node.o AStarTest.o
	g++ Node.o AStarTest.o -o AStarTest 

Node.o: Node.cpp Node.h
	g++ -g -c Node.cpp

AStarTest.o: Node.o AStarTest.cpp AStarTest.h
	g++ -g -c AStarTest.cpp

clean:
	rm -rf *.o AStarTest
