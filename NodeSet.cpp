#include "NodeSet.h"

using namespace std;

std::vector<Node>::iterator NodeSet::find(Node n1)
{
	for (vector<Node>::iterator it; it != nodeSet.end(); it++) {
		if ((*it) == n1) {
			return it;	
		}
	}

	return nodeSet.end();
}

void NodeSet::insert(Node n1) 
{
	if (find(n1) == nodeSet.end()) {
		nodeSet.push_back(n1);
	}
}

void NodeSet::erase(Node n1) 
{
	vector<Node>::iterator it = find(n1);

	if (it != nodeSet.end()) {
		nodeSet.erase(it);
	}

	return;
}
