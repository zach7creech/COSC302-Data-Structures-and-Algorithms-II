/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Challenge 05: Graph Paths
 * This program reads in a series of directed graphs from standard input, along with a number of
 * proposed paths within the graph. The program checks if each of these proposed paths, otherwise
 * described as possible connections between nodes, is valid. It then outputs whether it is possible
 * to go from node 'A' to node 'B'.
 * 02/18/2020 */

#include <map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

bool traverse(char, char, map<char, vector<char> > &, vector<char> &);

int main(int argc, char *argv[]) 
{
	map<char, vector<char> > paths;
	vector<char> visited;

	int nedges, npaths, graph = 1;
	char src, dst;
	
	while(cin >> nedges)
	{
		//needs to be a space between each graph's output
		if(graph != 1)
			cout << '\n';

		//paths is the map that is keyed on a node whose value is a vector of nodes you can travel TO from it
		//and must be cleared for each new graph
		paths.clear();
		
		//reads in all of the source/destination pairs from standard input (creates the graph)
		for(int i = 0; i < nedges; i++)
		{
			cin >> src >> dst;
			paths[src].push_back(dst);
		}
		
		cin >> npaths;
		//read in the proposed paths one by one, and for each one decide if it is a valid path
		for(int i = 0; i < npaths; i++)
		{
			cin >> src >> dst;
			//call recursive function traverse() to see if the destination can be reached from the source and
			//print relevant message to standard output
			if(traverse(src, dst, paths, visited))
				cout << "In Graph " << graph << " there is a path from " << src << " to " << dst << '\n';
			else
				cout << "In Graph " << graph << " there is no path from " << src << " to " << dst << '\n';
			//visited keeps track of which nodes have already been visited in the current search for path validity to avoid
			//infinite loops, and it must be cleared between traversals
			visited.clear();
		}
		//keep track of which graph is being analyzed (numerical order)
		graph++;
	}
	return 0;
}

//recursive function that traverse the graph, visiting every possible path from a given source to every leaf destination until
//the target destination is reached or every leaf is reached without finding the target
bool traverse(char src, char dst, map<char, vector<char> > &paths, vector<char> &visited)
{	
	//check that the current "source" node has not already been visited, avoiding infinite looping
	for(unsigned int i = 0; i < visited.size(); i++)
		if(src == visited[i])
			return false;

	//made it to this source node for the first time
	visited.push_back(src);
	
	//first check every direct path from source to the next destination to see if target is there
	for(unsigned int i = 0; i < paths[src].size(); i++)
	{
		if(paths[src][i] == dst)
			return true;
	}
	//if the target isn't directly connected to the current source, check each of this source's connections by calling traverse() again on each of them
	for(unsigned int i = 0; i < paths[src].size(); i++)
	{
		if(traverse(paths[src][i], dst, paths, visited))
			return true;
	}
	//if none of the current source's connected nodes found the target, then there is no path from this source to the target
	return false;
}
