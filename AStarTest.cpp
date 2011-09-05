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

/*
bool fnequals(Node n1, Node n2) 
{
	if (n1.x == n2.x) {
		if (fabs(n1.y - (GRAPH_HEIGHT-1)) < fabs(n2.y - (GRAPH_HEIGHT-1))) {
			return true;
		} else {
			return false;
		}
	} else if (n1.x < n2.x) {
		return true;
	} else {
		return false;
	}
} */

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

void reconstruct_path(map<pair<int, int>, Node>& parent, Node& current, list<Node>& path) 
{
	if (parent.find(make_pair(current.x, current.y)) != parent.end()) {
		reconstruct_path(parent, parent[make_pair(current.x, current.y)], path);
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
	openSet.insert(make_pair(start.x, start.y));

	g_score[make_pair((start.x), (start.y))] = 0;
	h_score[make_pair((start.x), (start.y))] = dist_between(start, goal);
	f_score[make_pair((start.x), (start.y))] = h_score[make_pair(start.x, start.y)];


	while (!openSet.empty()) {
		n1.x = (*(openSet.begin())).first;
		n1.y = (*(openSet.begin())).second;

		// check for lowest f_score among openSet
		for (set<pair<int, int> >::iterator it = openSet.begin(); it != openSet.end(); it++) {
			if (f_score[make_pair((*it).first, (*it).second)] < f_score[make_pair(n1.x, n1.y)]) {
				n1.x = (*it).first;
				n1.y = (*it).second;
			}
		}

		if (n1 == goal) {
			reconstruct_path(navigated, n1, path);	
			return path;
		}

		openSet.erase(make_pair(n1.x, n1.y));
		closedSet.insert(make_pair(n1.x, n1.y));

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
			
			if (closedSet.find(make_pair((*n2).x, (*n2).y)) != closedSet.end()) {
				continue;
			}

			float tentative_g_score = g_score[make_pair(n1.x, n1.y)] + dist_between(n1, *n2);
				
			if (openSet.find(make_pair((*n2).x, (*n2).y)) == openSet.end()) {
				openSet.insert(make_pair((*n2).x, (*n2).y));
				tentative_is_better = true;
			} 
			else if (tentative_g_score < g_score[make_pair((*n2).x, (*n2).y)]) {
				tentative_is_better = true;
			}
			
			if (tentative_is_better) {
				navigated[make_pair((*n2).x, (*n2).y)] = n1;
				g_score[make_pair((*n2).x, (*n2).y)] = tentative_g_score;
				h_score[make_pair((*n2).x, (*n2).y)] = dist_between(*n2, goal);
				f_score[make_pair((*n2).x, (*n2).y)] = g_score[make_pair((*n2).x, (*n2).y)] + h_score[make_pair((*n2).x, (*n2).y)];
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
