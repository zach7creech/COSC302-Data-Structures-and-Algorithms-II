#include "volsort.h"
#include <iostream>

List::List() 
{
	head = nullptr;
	size = 0;
}

List::~List() 
{
	Node* tmp;
	Node* n = head;

	//Delete all of the dynamic memory allocated to the list
	while(n != nullptr)
	{
		tmp = n;
		n = n->next;
		delete tmp;
	}
}
