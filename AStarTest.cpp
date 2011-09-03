#include <iostream>
#include <set>
#include <map>
#include <cmath>

using namespace std;

int graph[5][5] = 
{
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
	0, 0, 0, 1, 0,
	0, 0, 0, 0, 0,
};

struct Node 
{
	friend bool operator<(const Node& n1, const Node& n2);
	friend bool operator==(const Node& n1, const Node& n2);
	int x;
	int y;
};

bool operator<(const Node& n1, const Node& n2) 
{
	if (n1.x < n2.x) {
		return true;
	}

	return false;
}

bool operator==(const Node& n1, const Node& n2) 
{
	if (n1.x == n2.x && n1.y == n2.y) {
		return true;
	}

	return false;
}

int calc_heuristic(Node start, Node goal) 
{
	int dist = 0;
	
	int x = fabs(start.x - goal.x);
	int y = fabs(start.y - goal.y);
	
	dist = floor(sqrt(x*x + y*y));

	return dist;
}

bool AStar(Node start, Node goal) 
{
	Node x;
	Node y;

	// declarations
	set<Node> closedSet;
	set<Node> openSet; 	
	int navigated[5][5] = {0};

	map<Node, int> g_score;
	map<Node, int> h_score;
	map<Node, int> f_score;

	// initializations
	openSet.insert(start);

	g_score[start] = 0;
	h_score[start] = calc_heuristic(start, goal);
	f_score[start] = h_score[start];

	while (!openSet.empty()) {

		set<Node>::iterator it = openSet.begin();
		x = *it;

		// check for lowest f_score among openSet
		for (; it != openSet.end(); it++) {
			if (f_score[*it] < f_score[x]) {
				x = *it;	
			}
		}

		if (x == goal) {
			
		}


	}


}




int main (int argc, char* argv[]) 
{
	Node start = {0, 5}; 
	Node goal = {5, 5};

	cout << start.x << "," << start.y << endl;
	cout << goal.x << "," << goal.y << endl;


}
