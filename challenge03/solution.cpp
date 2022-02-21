/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Challenge 03: Palindrome Permutation
 * This program reads phrases from standard input and calculates if each phrase is or is not a 
 * palindrome permutation. The program uses an unordered_map to store the number of times each 
 * character appears in the phrase. If there is more than one character that appears an ODD 
 * number of times, then the phrase is not a palindrome permutation.
 * 02/03/2020 */

#include <string>
#include <iostream>
#include <map>

using namespace std;

void is_palindrome(string);

int main(int argc, char *argv[]) 
{
	string phrase;
	//check each line of standard input with is_palindrome()
	while(getline(cin, phrase))
		is_palindrome(phrase);
	
	return 0;
}

//calculates if a phrase is a palindrome permutation by counting instances of unique characters
void is_palindrome(string phrase)
{
	int num_odd = 0;
	map<char, int> counter;
	//loop through each character of the phrase to disregard it or add it to the map
	for(unsigned int i = 0; i < phrase.size(); i++)
	{
		//characters that are not letters are ignored
		if(phrase[i] < 65 || (phrase[i] > 90 && phrase[i] < 97) || phrase[i] > 122)
				continue;
		//if the current character is not already in the map, add it, set its count to 1, and increment odd number counter
		if(counter.find(phrase[i]) == counter.end())
		{	
			counter[phrase[i]] = 1;
			num_odd++;
		}
		//otherwise the current character's count just needs to be incremented and checked if it is now odd or even
		else
		{	
			counter[phrase[i]]++;
			if(counter[phrase[i]] % 2 == 0)
				num_odd--;
			else
				num_odd++;
		}
	}
	//at MOST one character can appear an odd number of times in a phrase for the phrase to be a palindrome permutation
	if(num_odd > 1)
		cout << "\"" << phrase << "\" is not a palindrome permutation\n";
	else
		cout << "\"" << phrase << "\" is a palindrome permutation\n";
}
