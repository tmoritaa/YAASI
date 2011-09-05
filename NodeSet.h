#ifndef _NODESET_H_
#define _NODESET_H_

#include <vector>
#include "Node.h"

class NodeSet 
{
private:
	std::vector<Node> nodeSet;

public:
	void erase(Node n1);
	void insert(Node n1);
	std::vector<Node>::iterator find(Node n1);
};

#endif
