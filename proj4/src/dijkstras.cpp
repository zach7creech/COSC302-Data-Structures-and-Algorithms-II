/* Authors: Nicholas Creech and Zachery Creech
 * COSC302 Spring 2020
 * Project 4 - Path Finding: dijkstra.cpp
 * Create a program that reads in a grid of terrain tiles on standard input and uses 
 * Dijkstra's Aglgorithm to find the shortest path from a starting tile to an end tile.
 * 03/11/2020 */ 

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct Node 
{	
	int x, y;
	int weight;
	int distance;
	char type;
	bool visited;
	
	Node *backedge;
	vector<Node*> adj;
};

int main(int argc, char *argv[]) 
{
	//read in all terrain types
	
	map<char, int> tile_cost;
	multimap<int, Node*> currentPath;
	vector<Node*> shortestPath;
	vector<Node*> visited;
	int num_tiles;
	char type;
	int cost;

	cin >> num_tiles;
	
	for(int i = 0; i < num_tiles; i++)
	{
		cin >> type >> cost;
		tile_cost[type] = cost;
	}

	//create grid

	int row, col;
	vector<vector<Node*> > grid;

	cin >> row >> col;
	grid.resize(row);
	
	for(int x = 0; x < row; x++)
	{
		for(int y = 0; y < col; y++)
		{
			//creates each new node as it goes and assigns all member variables
			cin >> type;
			Node *new_node = new Node;
			new_node->x = x;
			new_node->y = y;
			new_node->type = type;
			//the weight of the tile is dependent on the type, found in the tile_cost map
			new_node->weight = tile_cost.find(type)->second;
			new_node->distance = -1;
			new_node->visited = false;
			new_node->backedge = NULL;
			grid[x].push_back(new_node);
		}
	}
	 
	//create adjacency list for each node by adding neighboring nodes (if they exist) to the adj vector member
	
	Node *cur_node;

	for(int x = 0; x < row; x++)
	{
		for(int y = 0; y < col; y++)
		{
			cur_node = grid[x][y];
			//top
			if(x - 1 >= 0)
				cur_node->adj.push_back(grid[x - 1][y]);	
			//right
			if(y + 1 < col)
				cur_node->adj.push_back(grid[x][y + 1]);
			//bottom
			if(x + 1 < row)
				cur_node->adj.push_back(grid[x + 1][y]);
			//left
			if(y - 1 >= 0)
				cur_node->adj.push_back(grid[x][y - 1]);
		}
	}
	
	//Dijkstra's algorithm
	int startX, startY, endX, endY;
	cin >> startX >> startY >> endX >> endY;

	//Insert starting node
	Node* startNode = grid[startX][startY];
	startNode->distance = 0;
	currentPath.insert(make_pair(startNode->distance, startNode));

	//Run the algorithm until all nodes have been visited
	while(visited.size() != (unsigned int)row * col)
	{
		Node* currentNode;

		//Remove node and skip if distance is not equal to key distance (the node is elsewhere in the map with an updated distance)
		if(currentPath.begin()->first != currentPath.begin()->second->distance)
		{
			currentPath.erase(currentPath.begin());
			continue;
		}

		//Pop multimap and set current node's visited valu to true
		currentNode = currentPath.begin()->second;
		currentPath.erase(currentPath.begin());
		currentNode->visited = true;
		visited.push_back(currentNode);
		
		//Check adjacent nodes to find shortest path
		for(unsigned int x = 0; x < currentNode->adj.size(); x++)
		{
			//Only update a node if it has not been visited
			if(currentNode->adj[x] != NULL && !currentNode->adj[x]->visited)
			{	
				//Only update an adjacent node's distance if it's -1 or the new distance is less than the current one
				if(currentNode->adj[x]->distance == -1 || currentNode->distance + currentNode->weight < currentNode->adj[x]->distance)
				{
					currentNode->adj[x]->distance = currentNode->distance + currentNode->weight;
					currentNode->adj[x]->backedge = currentNode;
					
					//Add node to mulimap
					currentPath.insert(make_pair(currentNode->adj[x]->distance, currentNode->adj[x]));
				}
			}
		}
	}

	//Print shortest path's weight
	cout << grid[endX][endY]->distance << endl;

	Node* currentEdge = grid[endX][endY];
	while(currentEdge != NULL)
	{
		shortestPath.push_back(currentEdge);
		currentEdge = currentEdge->backedge;
	}

	//Print shortest path's backedge
	for(int x = shortestPath.size() - 1; x >= 0; x--)
		cout << shortestPath[x]->x << " " << shortestPath[x]->y << endl;

	//Free memory
	for(int x = 0; x < row; x++)
	{
		for(int y = 0; y < col; y++)
			delete grid[x][y];
	}

	return 0;
}
