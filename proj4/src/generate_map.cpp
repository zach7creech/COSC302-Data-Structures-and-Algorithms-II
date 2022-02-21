/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Project 4: generate_map.cpp
 * This program generates a random map of size n x n, where n is supplied as
 * a command line argument.
 * 03/11/2020 */

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	stringstream ss;
	ss << argv[1];
	
	int n;
	ss >> n;
	
	ofstream fout;
	fout.open("rand_map.txt");

	fout << "6\nf 3\ng 1\nG 2\nh 4\nm 7\nr 5\n" << n << ' ' << n << '\n';

	int rand_num;
	char tile;
	srand((int)time(0));

	//traverse the entire size of the grid, each node output a random tile character
	for(int x = 0; x < n; x++)
	{
		for(int y = 0; y < n; y++)
		{
			rand_num = rand() % 6;
			switch(rand_num)
			{
				case 0:
					tile = 'f';
					break;
				case 1:
					tile = 'g';
					break;
				case 2:
					tile = 'G';
					break;
				case 3:
					tile = 'h';
					break;
				case 4:
					tile = 'm';
					break;
				case 5:
					tile = 'r';
					break;
				default:
					break;
			}
			fout << tile;
			if(y != n - 1)
				fout << ' ';
		}
		fout << '\n';
	}

	fout << "0 0\n" << n - 1 << ' ' << n - 1 << '\n';
	fout.close();
	
	return 0;
}
