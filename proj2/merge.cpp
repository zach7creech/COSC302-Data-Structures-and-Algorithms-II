#include "volsort.h"
#include <iostream>

using namespace std;

Node *msort(Node *head, bool numeric);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right, bool numeric);

void merge_sort(List &l, bool numeric) 
{
	l.head = msort(l.head, numeric);
}

Node *msort(Node *head, bool numeric) 
{
	Node* left;
	Node* right;

	//Split list until sublists of size one are reached (base case)
	if(head->next != nullptr)
	{
		split(head, left, right);
		left = msort(left, numeric); //Recursively split left sublist
		right = msort(right, numeric); //Recursively split right sublist
 
		return merge(left, right, numeric); //Merge the split lists from single sublists to the full list
	}

	//Only one element left in sublist
	return head;
}

void split(Node *head, Node *&left, Node *&right) 
{
	Node* slow = head;
	Node* fast = head;

	//Once the loop finishes, slow will be at the middle node
	while(fast != nullptr && fast->next != nullptr)
	{
		fast = fast->next->next;

		//About to find middle; disconnect end of left sublist from right
		if(fast == nullptr || fast->next == nullptr)
		{
			Node* tmp = slow;
			slow = slow->next;
			tmp->next = nullptr;
		}

		else
			slow = slow->next;
	}

	//Set value of left and right in msort to heads of new left and right sublists
	left = head;
	right = slow;
}

Node *merge(Node *left, Node *right, bool numeric) 
{
	Node* lastNode = nullptr; //The most recent node added to sublist
	Node* head = nullptr; //New head of final, sorted/merged sublist

	//Merge until no elements are left in one of the sublists
	while(left != nullptr && right != nullptr)
	{
		if(numeric)
		{
			if(node_number_compare(left, right))
			{
				//Set head equal to head of left sublist
				if(head == nullptr)
					head = left;
				if(lastNode != nullptr)
					lastNode->next = left;

				//"Remove" the last element compared 
				lastNode = left;
				left = left->next;

				//Reached end of left sublist; attach to right
				if(left == nullptr)
					lastNode->next = right;
			}

			else
			{
				//Set head equal to head of right sublist
				if(head == nullptr)
					head = right;
				if(lastNode != nullptr)
					lastNode->next = right;

				//"Remove" the last element compared
				lastNode = right;
				right = right->next;

				//Reached the end of left sublist; attach to right
				if(right == nullptr)
					lastNode->next = left;
			}
		}

		else
		{
			if(node_string_compare(left, right))
			{
				if(head == nullptr)
					head = left;

				if(lastNode != nullptr)
					lastNode->next = left;

				lastNode = left;
				left = left->next;

				if(left == nullptr)
					lastNode->next = right;
			}

			else
			{
				if(head == nullptr)
					head = right;
				if(lastNode != nullptr)
					lastNode->next = right;

				lastNode = right;
				right = right->next;

				if(right == nullptr)
					lastNode->next = left;
			}

		}
	}

	//Return new head of sorted/merged sublist
	return head;
}

