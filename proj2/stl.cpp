// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void stl_sort(List &l, bool numeric) 
{
	vector<Node*> nodes;
	Node* n = l.head;

	//Add all nodes from list to vector to be sorted with std::sort
	while(n != nullptr)
	{
		nodes.push_back(n);
		n = n->next;
	}

	//Sort the vector
	if(numeric)
		sort(nodes.begin(), nodes.end(), node_number_compare);
	else
		sort(nodes.begin(), nodes.end(), node_string_compare);


	//Reattach the nodes in the list in the order of the sorted vector nodes
	for(unsigned int x = 0; x < nodes.size(); x++)
	{
		if(x != nodes.size() - 1)
			nodes[x]->next = nodes[x + 1];
		else
			nodes[x]->next = nullptr;
	}

	//Maintain new head
	l.head = nodes[0];
}

