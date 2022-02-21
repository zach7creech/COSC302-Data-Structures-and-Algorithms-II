#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <exception>

using namespace std;

int main(int argc, char** argv)
{
	srand((int)time(0));

	if(argc != 2)
		cout << "Usage: ./randList <size>\n";

	string sizeString = argv[1];
	int size;

	try{ size = stoi(sizeString); }
	catch(exception &e) { cout << "Invalid size. Size must be an int.\n"; return 1; };
	
	for(int x = 0; x < size; x++)
		cout << ((rand() % 100) + 1) << endl;

	return 0;
}
