#ifndef _ASTARTEST_H_
#define _ASTARTEST_H_

#include <list>
#include <map>

#include "Node.h"

void reconstruct_path(std::map<Node, Node>& parent, Node& current, std::list<Node>& path); 
std::list<Node> AStar(Node start, Node goal); 
float dist_between(Node start, Node goal); 
void populateNeighbours(Node node, std::list<Node>& neighbours); 
//bool fnequals(Node n1, Node n2); 

#endif 
