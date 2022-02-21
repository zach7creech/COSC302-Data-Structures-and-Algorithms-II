/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Challenge 04: solution.cpp
 * This program is supposed to read in an array from standard input, decide if
 * it is a maxheap, sort it into a minheap, then print the kth smallest element.
 * 02/14/2020 
 * Citation: heapify() and pop() came from Dr. Plank's notes on heaps */ 

#include <iostream>
#include <string>
#include <deque>
#include <sstream>

using namespace std;

bool is_maxheap(deque<int> &array, int size);

void heapify(int index, deque<int> &array);

void call_heapify(deque<int> &array, int size);

void pop(deque<int> &array, int size);

int main(int argc, char *argv[]) 
{
	string line;
	stringstream ss;

	while(getline(cin, line))
	{
		int size, k, num;
		char maxheap;
		deque<int> array;

		//read everything in using a stringstream
		ss.clear();
		ss.str(line);
		ss >> size >> k;
		getline(cin, line);
		ss.clear();
		ss.str(line);
		
		for(int i = 0; i < size; i++)
		{
			//creates the array of ints
			ss >> num;
			array.push_back(num);
		}

		//decide if the original array is a maxheap
		if(is_maxheap(array, array.size()))
			maxheap = 'Y';
		else
			maxheap = 'N';

		//calls heapify to create minheap
		call_heapify(array, array.size());
		
		//pops off the smallest number k times
		for(int i = 0; i < k - 1; i++)
			pop(array, array.size());

		//outputs information
		cout << maxheap << ' ' << array[0] << '\n';
	}
}

//decides if the array is a maxheap 
bool is_maxheap(deque<int> &array, int size)
{
	int lc, rc;
	//go through the entire array and check that each child satisifes the maxheap requirements
	for(int i = 0; i < array.size(); i++)
	{
		lc = 2*i + 1;
		rc = lc + 1;

		//if lc or rc is >= size then that index doesn't exist
		if(lc < array.size())
		{
			if(array[i] < array[lc])
				return false;
		}
		if(rc < array.size())
		{
			if(array[i] < array[rc])
				return false;
		}
	}
	return true;
}

//from Dr. Plank's notes, for given index check the children then make appropriate changes
void heapify(int index, deque<int> &array)
{
	unsigned int lc, rc;
	int tmp;

	while(1)
	{
		lc = index*2 + 1;
		rc = lc + 1;

		//if there aren't children then no changes need to be made
		if(lc >= array.size()) return;

		//if there isn't a right child or if the left child is <= the right child
		if(rc == array.size() || array[lc] <= array[rc])
		{
			//swap the left child with the parent if the parent is greater than it
			if(array[lc] < array[index])
			{
				tmp = array[lc];
				array[lc] = array[index];
				array[index] = tmp;
				index = lc;
			}
			else
				return;
		}
		//if the right child is less than the parent swap the right child with the parent
		else if(array[rc] < array[index])
		{
			tmp = array[rc];
			array[rc] = array[index];
			array[index] = tmp;
			index = rc;
		}
		else
			return;
	}
}

//calls heapify on every node in the array in order of level from bottom to top
void call_heapify(deque<int> &array, int size)
{
	int lc, leftmost, last_leftmost;
	//find leftmost index
	for(int i = 0; i < array.size(); i++)
	{
		lc = 2*i + 1;
		if(lc >= size)
			break;
		leftmost = lc;
	}
	//from this point index is the current index, leftmost has to be saved
	int index;
	index = leftmost;
	last_leftmost = leftmost;
	
	//calls heapify on the lowest level
	for(; index < array.size(); index++)
		heapify(index, array);

	//go to next level up's leftmost node
	leftmost = (leftmost - 1) / 2;
	index = leftmost;
	
	//run on every node including the root then stop
	while(1)
	{
		//call heapify on every node between current leftmost and last leftmost in the array
		for(; index < last_leftmost; index++)
			heapify(index, array);
		last_leftmost = leftmost;
		//stops the loop after calling heapify on root
		if(leftmost == 0)
			break;
		//go to next level
		leftmost = (leftmost - 1) / 2;
		index = leftmost;
	}
}

//from Dr. Plank's notes, pop off the smallest number then call heapify
void pop(deque<int> &array, int size)
{
	array[0] = array[array.size() - 1];
	array.pop_back();
	if(array.size() == 0) return;
	heapify(0, array);
}
