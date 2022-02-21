#include "volsort.h"
#include <exception>

/* Nicholas Creech and Zachery Creech
 * 2/6/20
 * Project02: Create a set of programs that sort a custom singly-linked list
 * using stl sort, qsort, merge sort, and quick sort
 */

using namespace std;

void List::push_front(const string& s)
{
	Node* newNode = new Node();
	newNode->string = s;

	//Try to convert string to int; default zero on exception
	try { newNode->number = stoi(s); }
	catch(exception& e) { newNode->number = 0; }

	//No node in list; make newNode the head
	if(size == 0)
	{
		newNode->next = nullptr;
		head = newNode;
	}

	//Attach newNode to old head; make newNode the head
	else
	{
		newNode->next = head;
		head = newNode;
	}

	//cout << "Pushed front " << newNode->string << endl;

	size++;
}

bool node_number_compare(const Node *a, const Node *b)
{
	return a->number < b->number;
}

bool node_string_compare(const Node *a, const Node *b)
{
	return a->string < b->string;
}

int qsort_number_compare(const void *a, const void *b)
{
	Node *a_n = *((Node**)a);
	Node *b_n = *((Node**)b);

	if(a_n->number < b_n->number) 
		return -1;
	if(a_n->number == b_n->number)
		return 0;
	if(a_n->number > b_n->number)
		return 1;

	return 0;
}

int qsort_string_compare(const void *a, const void *b)
{
	Node *a_n = *((Node**)a);
	Node *b_n = *((Node**)b);

	if(a_n->string < b_n->string)
		return -1;
	if(a_n->string == b_n->string)
		return 0;
	if(a_n->string > b_n->string)
		return 1;

	return 0;
}

void dump_node(Node *n)
{
	while(n != nullptr)
	{
		cout << "Node: (" << n->string << ", " << n->number << ")\n";
		n = n->next;
	}
}
