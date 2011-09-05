#include <iostream>
#include <set>
#include <map>
#include <list>
#include <cmath>
#include <utility>

#include "Node.h"
#include "AStarTest.h"
#include "Graph.h"

using namespace std;

int DEBUG;

int graph[GRAPH_HEIGHT][GRAPH_WIDTH] = 
{
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 0, 1, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

/*
int graph[GRAPH_HEIGHT][GRAPH_WIDTH] =
{
	{0, 0, 0, 0 ,0},
	{1, 1, 1, 1 ,0},
	{0, 0, 0, 1 ,0},
	{0, 0, 0, 1 ,0},
	{0, 0, 0, 0 ,0}
};*/

inline pair<int, int> nodeToPair(Node n1) 
{
	return make_pair(n1.x, n1.y);
}

inline Node pairToNode(pair<int, int> p1) 
{
	Node n = {p1.first, p1.second};

	return n;
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

inline float dist_between(Node n1, Node n2) 
{
	float dist = 0;

	float x = fabs(n1.x - n2.x);
	float y = fabs(n1.y - n2.y);

	dist = sqrt(y*y + x*x);

	return dist;
}

void reconstruct_path(map<pair<int, int>, Node>& parent, Node& current, list<Node>& path) 
{
	if (parent.find(nodeToPair(current)) != parent.end()) {
		reconstruct_path(parent, parent[nodeToPair(current)], path);
	}

	path.push_back(current);
}

list<Node> AStar(Node start, Node goal) 
{
	// declarations
	Node n1;

	//bool (*fn_pt)(Node, Node) = fnequals;

	//set<Node, bool(*)(Node,Node)> closedSet(fn_pt);
	//set<Node, bool(*)(Node,Node)> openSet(fn_pt); 	
	set<pair<int, int> > closedSet;
	set<pair<int, int> > openSet;

	map<pair<int, int>, Node> navigated;

	map<pair<int, int>, float> g_score;
	map<pair<int, int>, float> h_score;
	map<pair<int, int>, float> f_score;

	list<Node> path;
	list<Node> neighbours;

	// initializations
	openSet.insert(nodeToPair(start));

	g_score[nodeToPair(start)] = 0;
	h_score[nodeToPair(start)] = dist_between(start, goal);
	f_score[nodeToPair(start)] = h_score[nodeToPair(start)];


	while (!openSet.empty()) {
		n1 = pairToNode(*(openSet.begin()));

		//n1.x = (*(openSet.begin())).first;
		//n1.y = (*(openSet.begin())).second;

		// check for lowest f_score among openSet
		for (set<pair<int, int> >::iterator it = openSet.begin(); it != openSet.end(); it++) {
			if (f_score[*it] < f_score[nodeToPair(n1)]) {
				n1 = pairToNode(*it);

				//n1.x = (*it).first;
				//n1.y = (*it).second;
			}
		}

		if (n1 == goal) {
			reconstruct_path(navigated, n1, path);	
			return path;
		}

		openSet.erase(nodeToPair(n1));
		closedSet.insert(nodeToPair(n1));

		neighbours.clear();
		populateNeighbours(n1, neighbours);

		if (DEBUG) {
			cout << "---------New Node-----------" << endl;
			cout << "Current Node: " << endl;
			cout << n1.x << "," << n1.y << endl;
			cout << "-----------------------------" << endl;

			cout << "Neighbours: " << endl;
			for (list<Node>::iterator n2 = neighbours.begin(); n2 != neighbours.end(); n2++) {
				cout << (*n2).x << "," << (*n2).y << endl;
			}
			cout << "-----------------------------" << endl;
		
			cout << "OpenSet: " << endl;
			for (set<pair<int, int> >::iterator n2 = openSet.begin(); n2 != openSet.end(); n2++) {
				cout << (*n2).first << "," << (*n2).second << endl;
			}
			cout << "-----------------------------" << endl;

			cout << "ClosedSet: " << endl;
			for (set<pair<int, int> >::iterator n2 = closedSet.begin(); n2 != closedSet.end(); n2++) {
				cout << (*n2).first << "," << (*n2).second << endl;
			}
			cout << "-----------------------------" << endl;
		}

		for (list<Node>::iterator n2 = neighbours.begin(); n2 != neighbours.end(); n2++) {
			bool tentative_is_better = false;
			
			if (closedSet.find(nodeToPair(*n2)) != closedSet.end()) {
				continue;
			}

			float tentative_g_score = g_score[nodeToPair(n1)] + dist_between(n1, *n2);
				
			if (openSet.find(nodeToPair(*n2)) == openSet.end()) {
				openSet.insert(nodeToPair(*n2));
				tentative_is_better = true;
			} 
			else if (tentative_g_score < g_score[nodeToPair(*n2)]) {
				tentative_is_better = true;
			}
			
			if (tentative_is_better) {
				navigated[nodeToPair(*n2)] = n1;
				g_score[nodeToPair(*n2)] = tentative_g_score;
				h_score[nodeToPair(*n2)] = dist_between(*n2, goal);
				f_score[nodeToPair(*n2)] = g_score[nodeToPair(*n2)] + h_score[nodeToPair(*n2)];
			}
		}
	}

	// failed case
	cout << "No Path Found" << endl;
	return path;
}

int main (int argc, char* argv[]) 
{
	DEBUG = argc - 1;

	Node start = {0, GRAPH_HEIGHT-1}; 
	Node goal = {GRAPH_WIDTH-1, 0};

	list<Node> path;

	path = AStar(start, goal);

	for (list<Node>::iterator it = path.begin(); it != path.end(); it++) {
		cout << (*it).x << "," << (*it).y << endl;
	}
}
