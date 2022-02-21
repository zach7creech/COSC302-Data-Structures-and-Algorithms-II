/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Challenge01: solution.cpp
 * This program performs rotations on a user-provided array,
 * shifting elements either left or right in a loop.
 * 01/16/2020 */

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) 
{
    int size, rot, newInd;
	char direct;
	vector<int> vec;
	
	//as long as a size is provided, keep reading data
	while(cin >> size)
	{
    	cin >> rot >> direct;
		/* rotations happen in a loop, so the greatest number of rotations before returning the same
		 * array is rot % size. Basically, if the number of rotations is divisible evenly by the size
		 * of the array, then no rotations need to be performed at all */
		rot = rot % size;
		//resized to the correct size of current array
		vec.resize(size);
		//loops enough times to get all elements from standard input using size as condition
		for(int i = 0; i < size; i++)
		{
			//"rotated index" is calculated as the element is read in
			if(direct == 'L')
			{	
				/* if going to the left, the new index is the element's original index minus the number of rotations.
				 * if that new index is negative, the size of the array must be added */
				newInd = i - rot;
				if(newInd < 0)
					newInd += size;
				cin >> vec[newInd];
			}
			else
			{	
				/* if going to the right, the new index is the element's original index plus the number of rotations.
				 * if that new index is greater than the size of the array, the size of the array must ne subracted */
				newInd = i + rot;
				if(newInd > size - 1)
					newInd -= size;
				cin >> vec[newInd];
			}
		}
		//print out all elements in their corrected order with proper formatting
		for(int i = 0; i < size - 1; i++)
			cout << vec[i] << ' ';
		cout << vec[size - 1] << '\n';
	}
	return 0;
}
