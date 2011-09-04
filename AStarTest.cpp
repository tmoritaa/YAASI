#include <iostream>
#include <set>
#include <map>
#include <list>
#include <cmath>

int DEBUG;
const int GRAPH_WIDTH = 5;
const int GRAPH_HEIGHT = 5;

using namespace std;

int graph[GRAPH_HEIGHT][GRAPH_WIDTH] = 
{
	{0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0},
	{0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0}
};

struct Node 
{
	//friend bool operator<(const Node& n1, const Node& n2);
	friend bool operator==(const Node& n1, const Node& n2);
	int x;
	int y;
};

bool operator<(const Node& n1, const Node& n2) 
{
	if (n1.x <= n2.x && n1.y <= n2.y) {
		return true;
	}

	return false;
}

bool operator==(const Node& n1, const Node& n2) 
{
	if (n1.y == n2.y && n1.x == n2.x) {
		return true;
	}

	return false;
}

bool fnequals(Node n1, Node n2) 
{
	float n1temp = sqrt((n1.x)*(n1.x) + (n1.y)*(n1.y));
	float n2temp = sqrt((n2.x)*(n2.x) + (n2.y)*(n2.y));

	if (n1temp < n2temp) {
		return true;
	}

	return false;
}

void populateNeighbours(Node node, list<Node>& neighbours) 
{
	Node temp;

	for (int x = -1; x <= 1; x++) {
		if (node.x + x < 0 || node.x + x > (GRAPH_WIDTH - 1)) {
			continue;
		}

		for (int y = -1; y <= 1; y++) {
			if (node.y + y < 0 || node.y + y > (GRAPH_HEIGHT - 1) || (y == 0 && x == 0)) {
				continue;
			}

			temp.x = node.x + x;
			temp.y = node.y + y;

			if (graph[temp.y][temp.x] == 0) {
				neighbours.push_back(temp);
			}
		}
	}
}

inline float dist_between(Node start, Node goal) 
{
	float dist = 0;

	float y = fabs(start.y - goal.y);
	float x = fabs(start.x - goal.x);

	dist = sqrt(y*y + x*x);

	return dist;
}

void reconstruct_path(map<Node, Node>& parent, Node& current, list<Node>& path) 
{
	if (parent.find(current) != parent.end()) {
		reconstruct_path(parent, parent[current], path);
	}

	path.push_front(current);
}

list<Node> AStar(Node start, Node goal) 
{
	Node n1;

	// declarations
	bool (*fn_pt)(Node, Node) = fnequals;

	set<Node, bool(*)(Node,Node)> closedSet(fn_pt);
	set<Node, bool(*)(Node,Node)> openSet(fn_pt); 	
	map<Node, Node> navigated;

	map<Node, float> g_score;
	map<Node, float> h_score;
	map<Node, float> f_score;

	list<Node> path;
	list<Node> neighbours;

	// initializations
	openSet.insert(start);

	g_score[start] = 0;
	h_score[start] = dist_between(start, goal);
	f_score[start] = h_score[start];


	while (!openSet.empty()) {
		n1 = *(openSet.begin());
		neighbours.clear();

		// check for lowest f_score among openSet
		for (set<Node>::iterator it = openSet.begin(); it != openSet.end(); it++) {
			if (f_score[*it] < f_score[n1]) {
				n1 = *it;	
			}
		}

		if (n1 == goal) {
			reconstruct_path(navigated, n1, path);	
			return path;
		}

		openSet.erase(n1);
		/*set<Node>::iterator er;
		er = openSet.find(n1);

		if (er != openSet.end()) {
			openSet.erase(er);
		}*/

		closedSet.insert(n1);

		populateNeighbours(n1, neighbours);

		if (DEBUG) {

			cout << "Neighbours: " << endl;
			for (list<Node>::iterator n2 = neighbours.begin(); n2 != neighbours.end(); n2++) {
				cout << (*n2).x << "," << (*n2).y << endl;
			}
			cout << "-----------------------------" << endl;
		
			cout << "OpenSet: " << endl;
			for (set<Node>::iterator n2 = openSet.begin(); n2 != openSet.end(); n2++) {
				cout << (*n2).x << "," << (*n2).y << endl;
			}
			cout << "-----------------------------" << endl;

			cout << "ClosedSet: " << endl;
			for (set<Node>::iterator n2 = closedSet.begin(); n2 != closedSet.end(); n2++) {
				cout << (*n2).x << "," << (*n2).y << endl;
			}
			cout << "-----------------------------" << endl;
		}

		for (list<Node>::iterator n2 = neighbours.begin(); n2 != neighbours.end(); n2++) {
			bool tentative_is_better = false;
			
			if (closedSet.find(*n2) != closedSet.end()) {
				continue;
			}

			float tentative_g_score = g_score[n1] + dist_between(n1, *n2);
				
			if (openSet.find(*n2) == openSet.end()) {
				openSet.insert(*n2);
				tentative_is_better = true;
			} 
			else if (tentative_g_score < g_score[*n2]) {
				tentative_is_better = true;
			}
			
			if (tentative_is_better) {
				navigated[*n2] = n1;
				g_score[*n2] = tentative_g_score;
				h_score[*n2] = dist_between(*n2, goal);
				f_score[*n2] = g_score[*n2] + h_score[*n2];
			}
		}
	}

	return path;
}

int main (int argc, char* argv[]) 
{
	DEBUG = argc - 1;

	Node start = {0, 4}; 
	Node goal = {4, 0};

	list<Node> path;

	path = AStar(start, goal);

	for (list<Node>::iterator it = path.begin(); it != path.end(); it++) {
		cout << (*it).x << "," << (*it).y << endl;
	}
}
