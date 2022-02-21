/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Challenge 02: Closest Numbers
 * This program reads arrays of numbers from standard input and finds the pair or
 * pairs of numbers that are closest together (have the smallest absolute difference) 
 * in each array. The program then outputs those pairs to standard output.
 * 01/26/2020 */

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    
	int size, curNum, dif, ldif;
	//nums contains all the numbers in the array in SORTED order least -> greatest
	//smallest contains the index (or indices) of the smaller number in the pair(s) of smallest difference
	//ex: if the pair with smallest difference is 1,8 then smallest would store the index of 1 in nums, the index of 8 is just ind(1) + 1
	vector<int> nums, smallest;
	while(cin >> size)
	{
		nums.clear();
		smallest.clear();
		
		//read in every number in given array and store them in nums, unsorted
		for(int i = 0; i < size; i++)
		{
			cin >> curNum;
			nums.push_back(curNum);
		}
		
		//sorts nums from least to greatest
		sort(nums.begin(), nums.end());

		//find the pair(s) with smallest difference by finding the difference between every number and the one greater than it
		for(int i = 0; i < size - 1; i++)
		{
			dif = abs(nums[i + 1] - nums[i]);
			//for the pair nums[0],nums[1] there is no ldif, so it is the smallest when no other pair has been examined
			if(i == 0)
			{
				smallest.push_back(i);
				ldif = dif;
				continue;
			}
			//for every subsequent comparison the current difference (dif) is compared to the last difference (ldif)
			if(dif < ldif)
			{	
				//if new smallest difference is found then smallest must be cleared and its contents replaced with the new smallest pair
				smallest.clear();
				smallest.push_back(i);
				ldif = dif;
			}
			//if the same smallest difference is found for another pair then the current pair must be ADDED to smallest without changing the current contents
			else if(dif == ldif)		
				smallest.push_back(i);
		}
		
		//prints the smallest pairs with correct formatting to standard output
		for(unsigned int i = 0; i < smallest.size(); i++)
		{
			cout << nums[smallest[i]] << ' ' << nums[smallest[i] + 1];
			if(i != smallest.size() - 1)
				cout << ' ';
			else
				cout << '\n';
		}
	}
	
	return EXIT_SUCCESS;
}
