/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Challenge 08: Adding List-Based Integers
 * This program implements a templated doubly-linked list data structure and uses 
 * it to store and add integers. Each node in the list represents one digit of 
 * the integer.
 * 03/27/2020 */

#include <iostream>
#include <string>

using namespace std;

template <class T>
struct Node
{
	Node<T> *flink, *blink;
	T data;
};

template <class T>
class List
{
	Node<T> *sentinel;
	int size;

public:	
	List();
	List<T> operator= (List<T> l);
	void Clear();

	T pop_back();
	T pop_front();
	void push_back(Node<T> *);
	void push_front(Node<T> *);
	
	int get_size() const;
	void listFromString(string integer);
};

template<class T>
List<T> Add(List<T> &int1, List<T> &int2);

int main(int argc, char *argv[]) 
{
	string first, second;

	//continue reading in integers until end of standard input
	while(cin >> first)
	{
		cin >> second;

		List<int> int1, int2, sum;
		
		//integers are read in as strings so each digit can be extracted individually and put into the List structure
		int1.listFromString(first);
		int2.listFromString(second);	
	
		//the integer with more digits is "int1" within the context of the Add function because it controls the outermost loop
		//this adds the integers and returns the list into sum
		sum = int1.get_size() > int2.get_size() ? Add(int1, int2) : Add(int2, int1);
		
		//print the integer by popping off the back of the list because back to front is most significant to least
		while(sum.get_size() > 0)
			cout << sum.pop_back();
		
		cout << '\n';

		//in lieu of a destructor, Clear() destroys the lists between loops
		int1.Clear();
		int2.Clear();
		sum.Clear();
	}
	
	return 0;
}

//constructor for the List structure, sets up the sentinel, assigns its flink and blink to itself, intitializes size to 0
template<class T>
List<T>::List()
{
	sentinel = new Node<T>;
	sentinel->data = -1;
	sentinel->flink = sentinel;
	sentinel->blink = sentinel;
	size = 0;
}

//operator overload for =, allows setting a List equal to another List while properly handling memory
template<class T>
List<T> List<T>::operator= (List<T> l)
{
	//create new copies of nodes from List to be copied and pushes them back on the receiving List
	while(l.get_size() > 0)
	{
		Node<T> *node = new Node<T>;
		node->data = l.pop_front();
		this->push_back(node);
	}
	//deletes the copied List
	l.Clear();

	return *this;
}

//although there isn't a point in this program where there would be anything left in a List before it is destroyed,
//this makes sure all nodes are deleted including the sentinel
template<class T>
void List<T>::Clear()
{
	while (size > 0)
		pop_front();

	delete sentinel;
}

//getter function for size
template<class T>
int List<T>::get_size() const
{
	return size;
}

//converts a given integer (represented as a string) into a List structure, every node representing a digit of the integer
template<class T>
void List<T>::listFromString(string integer)
{
	//visit every index of the string
	for(unsigned int i = 0; i < integer.size(); i++)
	{
		//convert char into an int
		int actualNum = integer[i] - '0';

		//create the new node and add it to the front of the List, because the List is ordered least significant -> most
		Node<T> *node = new Node<T>;

		node->data = actualNum;
		push_front(node);
	}
}

//pops off the last node in the List, destroying it and returning its data
template<class T>
T List<T>::pop_back()
{
	//fix all connections between nodes
	Node<T> *last = sentinel->blink, *secondLast = last->blink;
	sentinel->blink = secondLast;
	secondLast->flink = sentinel;

	T data = last->data;
	
	delete last;
	size--;
	return data;
}

//pops off the first node in the List, destroying it and returning its data
template<class T>
T List<T>::pop_front()
{
	//fix all connections between nodes
	Node<T> *first = sentinel->flink, *second = first->flink;
	sentinel->flink = second;
	second->blink = sentinel;
	
	T data = first->data;
	
	delete first;
	size--;
	return data;
}

//adds node to the back of the List
template<class T>
void List<T>::push_back(Node<T> *newNode)
{
	//unhook the sentinel from the back and insert new node
	Node<T> *origLast = sentinel->blink;
	origLast->flink = newNode;
	sentinel->blink = newNode;
	newNode->blink = origLast;
	newNode->flink = sentinel;
	size++;
}

//adds node to the front of the List
template<class T>
void List<T>::push_front(Node<T> *newNode)
{
	//unhook the sentinel from the front and insert new node
	Node<T> *origFirst = sentinel->flink;
	origFirst->blink = newNode;
	sentinel->flink = newNode;
	newNode->flink = origFirst;
	newNode->blink = sentinel;
	size++;
}

//adds two List structures (representing integers) and returns a List representing the sum
template<class T>
List<T> Add(List<T> &int1, List<T> &int2)
{
	List<int> sum;
	int digit1, digit2;
	int carry = 0;

	//as described in main(), int1 is the larger number and controls the outer loop. Any digits int1 has that
	//go beyond the most significant digit in int2 are just added to the end of the sum List
	while(int1.get_size() > 0)
	{	
		Node<int> *newDigit = new Node<int>;
		
		//examine least significant digit
		digit1 = int1.pop_front();
		
		//if all digits of int2 have been added to the sum, skip down to just add the remaining digits from int1
		if(int2.get_size() > 0)
		{	
			digit2 = int2.pop_front();

			//add the digits and the carry from the last sum
			newDigit->data = digit1 + digit2 + carry;
			
			//base 10 number so each digit must be less than 10, compute carry or set carry to 0
			if(newDigit->data > 9)
			{
				//the carry is whatever is in the tens place
				carry = newDigit->data / 10;
				//the digit is whatever is in the ones place
				newDigit->data %= 10;
			}
			else
				carry = 0;
			
			//add the newly computed digit to the sum List
			sum.push_back(newDigit);

			//in the event that the integers have the same number of digits, both integers will be exhausted at 
			//once and there might be a final carry to get the most significant digit
			if(int1.get_size() == 0 && carry != 0)
			{
				Node<int> *lastCarry = new Node<int>;
				lastCarry->data = carry;
				sum.push_back(lastCarry);
			}
		}
		else
		{
			//if int2 is exhausted then every remaining digit in int1 just needs to be added to the end of the sum List
			newDigit->data = digit1 + carry;
			//there could be a final carry from the last digit addition of int2, but after this runs once there will never be another carry
			carry = 0;
			
			sum.push_back(newDigit);
		}
	}
	
	return sum;
}
