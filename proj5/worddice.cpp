#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <map>

/* Nicholas Creech and Zachery Creech
 * 04/16/20
 * Project 5: Word Dice - 
 */ 

using namespace std;

struct Node
{
	string name;
	int index;
	vector<Node *> edges;
	Node *backedge;
};

class Graph
{
	public:
		Graph();
		~Graph();
		void clearLetters();
		bool BFS();
		Node *source;
		Node *sink;
		vector<Node *> dice;
		vector<Node *> letters;
		map<char, vector<Node *> > quickFind;
};

int main(int argc, char **argv)
{
	Graph graph;
	ifstream ifs;
	int index = 0;

	if(argc != 3)
	{
		cout << "Usage: ./worddice <dice_file> <word_file>\n";
		return 1;
	}

	ifs.open(argv[1]);

	//Read in dice
	string dice;
	while(ifs >> dice)
	{
		//cout << dice << endl;
		
		Node* n = new Node;
		
		n->name = dice;
		n->index = index;
		graph.dice.push_back(n);

		//Set up quick find for dice
		for(int x = 0; x < dice.size(); x++)
		{
			bool skip = false;

			//Prevent adding the same dice multiple times for the same letter
			for(int i = 0; i < graph.quickFind[dice[x]].size(); i++)
			{
				if(graph.quickFind[dice[x]][i] == n)
					skip = true;
			}

			if(!skip)
				graph.quickFind[dice[x]].push_back(n);
		}

		//Connect dice to source
		graph.source->edges.push_back(n);
	}

	/*
	cout << "START\n";
	map<char, vector<Node *> >::iterator mit;
	for(mit = graph.quickFind.begin(); mit != graph.quickFind.end(); mit++)
	{
		cout << mit->first << ": ";
		for(int x = 0; x < mit->second.size(); x++)
			cout << mit->second[x]->name << ' ';
	
		cout << '\n';
	}*/
	
	ifs.close();
	ifs.open(argv[2]);

	//Read in each word and determine if it can be made
	string word;
	while(ifs >> word)
	{
		//cout << "NEW WORD\n";
		//Reset graph to just the dice connected to the source
		graph.clearLetters();

		//Connect each letter of the word to each possible dice
		for(int x = 0; x < word.size(); x++)
		{
			for(int i = 0; i < graph.quickFind[word[x]].size(); i++)
			{
				//cout << "Connecting " << graph.quickFind[word[x]][i]->name << " to " << word[x] << endl;
						
				Node *letterNode = new Node;					
				letterNode->name = word[i];

				//Connect letter to sink
				letterNode->edges.push_back(graph.sink);
				graph.letters.push_back(letterNode);
					
				//Connect dice to letter
				graph.quickFind[word[x]][i]->edges.push_back(letterNode);
			}
		}

		//Process graph
	}

	ifs.close();

	return 0;
}

Graph::Graph()
{
	source = new Node;
	source->name = "Source";
	sink = new Node;
	sink->name = "Sink";
}

Graph::~Graph()
{	
	for(int x = 0; x < dice.size(); x++)
		delete dice[x];
	for(int x = 0; x < letters.size(); x++)
		delete letters[x];
}

void Graph::clearLetters()
{
	for(int x = 0; x < letters.size(); x++)
		delete letters[x];

	letters.clear();

	for(int x = 0; x < dice.size(); x++)
		dice[x]->edges.clear();
}

bool Graph::BFS()
{
	return true;
}
