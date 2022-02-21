/* Author: Zachery Creech
 * COSC302 Spring 2020
 * Challenge 06: Minimum Spanning Trees
 * This program reads in a matrix representing an undirected graph from standard
 * input and uses Prim's algorithm to find the minimum spanning tree. The edges
 * and total weight are then printed to standard output. This is repeated as long 
 * as the program receives input.
 * 03/07/2020 */

#include <vector>
#include <iostream>
#include <set>
#include <map>

using namespace std;

int main(int argc, char *argv[]) 
{
	unsigned int num_vertices;
	int weight = -5;
	
	//when end of standard input is reached, stop
	while(cin >> num_vertices)
	{
		//needs to be a space between each graph's output
		if(weight != -5)
			cout << '\n';
		
		//read in entire graph, store as vector of vectors
		vector< vector<int> > adjacency(num_vertices);
		for(unsigned int i = 0; i < num_vertices; i++)
		{
			for(unsigned int j = 0; j < num_vertices; j++)
			{
				cin >> weight;
				adjacency[i].push_back(weight);
			}
		}

		set<pair<int, int> > edges;
		multimap<int, pair<int,int> > weights;
		pair<int,int> curEdge;
		set<int> nodes;
		int totalWeight = 0;
		
		//always start at node 0, add to nodes set
		int curNode = 0;
		nodes.insert(curNode);

		//everything up until while loop is for node 0
		//find every legal edge connected to current node and add to multimap
		for(unsigned int i = 0; i < num_vertices; i++)
		{
			if(adjacency[curNode][i] == -1)
				continue;
			weights.insert(make_pair(adjacency[curNode][i], make_pair(curNode, i)));
		}
	
		//the smallest weighted edge is first in the multimap
		edges.insert(weights.begin()->second);
		//update total weight
		totalWeight += weights.begin()->first;
		//move to the next node (following smallest weighted edge)
		curNode = weights.begin()->second.second;
		//pop off that pair from the multimap as per Prim's algorithm
		weights.erase(weights.begin());

		//continue process of Prim's algorithm until all nodes are visited (and therefore the graph has been entirely spanned)
		while(nodes.size() != num_vertices)
		{	
			//like before find all legal edges and add them to the multimap
			for(unsigned int i = 0; i < num_vertices; i++)
			{
				if(adjacency[curNode][i] == -1)
					continue;
				weights.insert(make_pair(adjacency[curNode][i], make_pair(curNode, i)));
			}
			
			curEdge = weights.begin()->second;
			
			//if either origin or destination node has already been accounted for in nodes set, erase it from the multimap
			//first edge that breaks this loop is an edge of interest
			while(nodes.find(curEdge.first) != nodes.end() && nodes.find(curEdge.second) != nodes.end())
			{
				weights.erase(weights.begin());
				curEdge = weights.begin()->second;
			}

			curNode = curEdge.second;
			nodes.insert(curNode);

			//this just fixes the order of how the edge is printed, formatting calls for "smaller" node to come first
			if(curEdge.first > curEdge.second)
			{
				int tmpNode = curEdge.first;
				curEdge.first = curEdge.second;
				curEdge.second = tmpNode;
			}
			//if current edge of interest has NOT already been accounted for, update total weight
			if(edges.find(curEdge) == edges.end())
				totalWeight += weights.begin()->first;
			
			//insert the edge of interest, pop it off the multimap, and start over
			edges.insert(curEdge);
			weights.erase(weights.begin());
		}

		//print out total weight of minimum spanning tree, then print out all edges that make up the tree
		cout << totalWeight << '\n';
		set<pair<int,int> >::iterator sitr;
	
		for(sitr = edges.begin(); sitr != edges.end(); sitr++)
		{
			char a = (*sitr).first + 'A', b = (*sitr).second + 'A';		
			cout << a << b << '\n';
		}
	}
	
	return 0;
}
