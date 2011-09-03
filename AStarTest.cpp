#include <iostream>
#include <set>
#include <map>

using namespace std;

int map[5][5] = {
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
	0, 0, 0, 1, 0,
	0, 0, 0, 0, 0,
};

struct Node {	
	int x;
	int y;
};


bool AStar(Node start, Node goal) {
	// declarations
	set<Node> closedSet;
	set<Node> openSet; 	
	int navigated[5][5] = {0};

	map<Node, int> g_score;
	map<Node, int> h_score;
	map<Node, int> f_score;

	// initializations
	openSet.insert(start);

	g_score[start] = 


}




int main (int argc, char* argv[]) 
{
	Node start = {0, 5}; 
	Node goal = {5, 5};

	cout << start.x << "," << start.y << endl;
	cout << goal.x << "," << goal.y << endl;


}
