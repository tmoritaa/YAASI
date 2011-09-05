#include <cmath>

#include "Node.h"
#include "Graph.h"

bool operator<(const Node& n1, const Node& n2) 
{
	float n1temp = sqrt((n1.x)*(n1.x) + (n1.y-(GRAPH_HEIGHT-1))*(n1.y-(GRAPH_HEIGHT-1)));
	float n2temp = sqrt((n2.x)*(n2.x) + (n2.y-(GRAPH_HEIGHT-1))*(n2.y-(GRAPH_HEIGHT-1)));

	if (n1temp < n2temp) {
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
