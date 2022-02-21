// quick.cpp

#include "volsort.h"

#include <iostream>

using namespace std;
// Prototypes

Node *qsort(Node *head, bool numeric);
void  partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric);
Node *concatenate(Node *left, Node *right);

// Implementations

void quick_sort(List &l, bool numeric) 
{
	l.head = qsort(l.head, numeric);
}

Node *qsort(Node *head, bool numeric) 
{
	if(head->next == nullptr)
	{	
		//cerr << "base case: " << head->number << '\n';
		return head;
	}
	Node *left = nullptr, *right = nullptr, *lefthead, *righthead;
	
	partition(head, head, left, right, numeric);
	//cerr << "out partition\n";
	//if(left->next == nullptr)
	//	cerr << "its what u thot\n";
	//cerr << "first number in left is " << left->number << '\n';
	//cerr << "first number in right is " << right->number << '\n';
	righthead = qsort(right, numeric);
	lefthead = qsort(left, numeric);

	//cerr << "concatenated\n";
	lefthead = concatenate(lefthead, righthead);

	return lefthead;
}

void partition(Node *head, Node *pivot, Node *&left, Node *&right, bool numeric) 
{
	//cerr << "in partition\n";
	Node *node = head->next;
	Node *lastleft = nullptr;
	Node *lastright = nullptr;

	if(numeric)
	{
		if(pivot->number < node->number)
		{
			left = pivot;
			lastleft = pivot;
			//cerr << "Added to left: " << lastleft->number << '\n';
		}
		else
		{
			right = pivot;
			lastright = pivot;
			//cerr << "Added to right: " << lastright->number << '\n';
		}

		while(node != nullptr)
		{
			if(node->number < pivot->number)
			{
				if(left == nullptr)
					left = node;
				else if(lastleft != nullptr)
					lastleft->next = node;
				lastleft = node;
				//cerr << "Added to left: " << lastleft->number << '\n';
			}
			else
			{
				if(right == nullptr)
					right = node;
				else if(lastright != nullptr)
					lastright->next = node;
				lastright = node;
				//cerr << "Added to right:" << lastright->number << '\n';
			}
			node = node->next;
		}
	}
	else
	{
		if(pivot->string < node->string)
		{
			left = pivot;
			lastleft = pivot;
		}
		else
		{
			right = pivot;
			lastright = pivot;
		}

		while(node != nullptr)
		{
			if(node->string < pivot->string)
			{
				if(left == nullptr)
					left = node;
				else
					lastleft->next = node;
				lastleft = node;
			}
			else
			{
				if(right == nullptr)
					right = node;
				else
					lastright->next = node;
				lastright = node;
			}
			node = node->next;
		}
	}
	//cerr << lastleft->number << ' ' << lastright->number << ' ' << "triggered\n";
	//if(lastleft->next == nullptr)
	//	cerr << "CUCK\n";
	
	if(lastleft != nullptr)
		lastleft->next = nullptr;
	if(lastright != nullptr)
		lastright->next = nullptr;
}

Node *concatenate(Node *left, Node *right) 
{
	//cerr << "concatenated " << left->number << ' ' << "to " << right->number << '\n';
	Node *node = left;
	while(node != nullptr && node->next != nullptr)
		node = node->next;

	node->next = right;

	return left;
}

