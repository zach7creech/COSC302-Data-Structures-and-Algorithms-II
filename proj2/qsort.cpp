// qsort.cpp

#include "volsort.h"

#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

void qsort_sort(List &l, bool numeric) 
{
	Node* nodes[l.size];
	Node* n = l.head;

	//Add all list nodes to new array of nodes to be sorted with std::qsort
	int index = 0;
	while(n != nullptr)
	{
		nodes[index] = n;
		n = n->next;
		index++;
	}

	//Sort the array of nodes
	if(numeric)
		qsort(nodes, l.size, sizeof(Node*), &qsort_number_compare);
	else
		qsort(nodes, l.size, sizeof(Node*), &qsort_string_compare);

	//Reattach the list nodes in the order of the sorted array nodes
	for(unsigned int x = 0; x < l.size; x++)
	{
		if(x != l.size - 1)
			nodes[x]->next = nodes[x + 1];
		else
			nodes[x]->next = nullptr;
	}

	//Maintain new head
	l.head = nodes[0];
}

