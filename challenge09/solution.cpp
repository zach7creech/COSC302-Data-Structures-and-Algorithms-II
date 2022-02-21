/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Challenge 09: Dynamic programming
 * This program reads in two genetic codes represented as strings from standard
 * input, then constructs a matrix with code1 as the columns and code2 as the 
 * rows to perform a sequence alignment algorithm. After performing the algorithm, 
 * the program outputs the "score" to standard output.
 * 04/18/2020 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) 
{
	//outer vector of matrix is the number of columns, inner vector is number of rows
	vector<vector<int> > matrix;
	
	//get both codes from standard input
	string code1, code2;
	getline(cin, code1);
	getline(cin, code2);
	
	//resize the matrix so that the number of columns equals code2 + 1 (for upper leftmost 0 spot)
	matrix.resize(code2.size() + 1);

	//resize the matrix so, for each column, the number of rows equals code1 + 1 (for upper leftmost 0 spot)
	//also fill the first row with 0, -1, -2, -3, etc
	for(unsigned int i = 0; i < matrix.size(); i++)
	{
		matrix[i].resize(code1.size() + 1);
		matrix[i][0] = i * -1;
	}

	//fill first column with 0, -1, -2, -3, etc
	for(unsigned int i = 0; i < matrix[0].size(); i++)
		matrix[0][i] = i * -1;
	
	
	int fromTop, fromLeft, diagonal, max;
	
	//go through all remaining empty spots in matrix row by row, starting at top left
	for(unsigned int i = 1; i < matrix.size(); i++)
	{
		for(unsigned int j = 1; j < matrix[0].size(); j++)
		{
			fromTop = matrix[i - 1][j] - 1;
			fromLeft = matrix[i][j - 1] - 1;
			
			//coming from the diagonal, if there's a match then add 1, if not then subtract 1
			if(code2[i - 1] == code1[j - 1])
				diagonal = matrix[i - 1][j - 1] + 1;
			else
				diagonal = matrix[i - 1][j - 1] - 1;

			//find maximum value of the three and assign it to current spot
			max = fromTop;

			if(fromLeft >= max)
				max = fromLeft;
			if(diagonal >= max)
				max = diagonal;

			matrix[i][j] = max;
		}
	}

	//answer is the bottom right corner spot of the matrix
	cout << matrix.back().back() << '\n';

	return 0;
}


