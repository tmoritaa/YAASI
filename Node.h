#ifndef _NODE_H_
#define _NODE_H_

struct Node 
{
	friend bool operator<(const Node& n1, const Node& n2);
	friend bool operator==(const Node& n1, const Node& n2);
	int x;
	int y;
};

bool operator<(const Node& n1, const Node& n2); 
bool operator==(const Node& n1, const Node& n2); 

#endif
