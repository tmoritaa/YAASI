all: AStarTest

AStarTest: Node.o NodeSet.o AStarTest.o
	g++ Node.o NodeSet.o AStarTest.o -o AStarTest 

Node.o: Node.cpp Node.h
	g++ -g -c Node.cpp

NodeSet.o: NodeSet.cpp NodeSet.h
	g++ -g -c NodeSet.cpp

AStarTest.o: Node.o AStarTest.cpp AStarTest.h
	g++ -g -c AStarTest.cpp

clean:
	rm -rf *.o AStarTest
