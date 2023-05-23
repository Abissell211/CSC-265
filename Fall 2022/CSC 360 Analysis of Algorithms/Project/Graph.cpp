#include "Graph.h"

Graph::Graph()
{
	srand(time(0));
	int rn;
	
	//initialize matrix
	int i, j;
	for(i = 0; i < NUMNODES; i++)
	{
		for(j = i + 1; j < NUMNODES; j++)
		{
			rn = rand() % 100 + 1;
			if(rn <= EDGEDENSITY)
			{
				matrix[i][j] = 1;
				matrix[j][i] = 1;
			}
			else
			{
				matrix[i][j] = 0;
				matrix[j][i] = 0;
			}
		}
	}
	
	//fill diagonal
	for(i = 0; i < NUMNODES; i++)
	{
		matrix[i][i] = 0;
	}
}

void Graph::printGraph()
{
	int i, j;
	
	for(i = 0; i < NUMNODES; i++)
	{
		cout << "Node " << i << ": \t";
		for(j = 0; j < NUMNODES; j++)
		{
			if(matrix[i][j] == 1)
			{
				cout << j << "  ";
			}
		}
		cout << endl;
	}
}

//returns number of nodes in the graph
int Graph::getNumNodes()
{
	return NUMNODES;
}

int * Graph::brute()
{
	int i, j, count, maxCount;
	bool validList, finFlag;
	
	maxCount = 0;
	
	//initialize arrays to zero
	for(i = 0; i < NUMNODES + 1; i++)
	{
		nodeList[i] = 0;
		nodeSet[i] = -1;
	}
	
	//iterate through every possible combination of nodes
	while(nodeList[NUMNODES] != 1)
	{
		//check if the current combination is valid
		validList = true;
		for(i = 0; i < NUMNODES - 1; i++)
		{
			if(nodeList[i] == 1)
			{
				for(j = i + 1; j < NUMNODES; j++)
				{
					if(nodeList[j] == 1 && matrix[i][j] == 1)
					{
						validList = false;
					}
				}
			}
		}
		
		//find out how many nodes are in the list
		count = 0;
		for(i = 0; i < NUMNODES; i++)
		{
			if(nodeList[i] == 1)
			{
				count++;
			}
		}
		
		//update the max count and the current greatest independent set if necessary
		if(validList && count > maxCount)
		{
			j = 0;
			maxCount = count;
			for(i = 0; i < NUMNODES; i++)
			{
				if(nodeList[i] == 1)
				{
					nodeSet[j] = i;
					j++;
				}
			}
		}
		
		//go to the next combination of nodes
		i = 0;
		finFlag = false;
		while(!finFlag)
		{
			if(nodeList[i] == 0)
			{
				nodeList[i] = 1;
				finFlag = true;
			}
			else if(nodeList[i] == 1)
			{
				nodeList[i] = 0;
				i++;
			}
		}
	}
	
	nodeSet[NUMNODES] = maxCount;
	return nodeSet;
}

int * Graph::greedy()
{
	bool finFlag = false;
	int i, j, numConnections, minConnections, minNode;
	int nodeCount = 0;
	
			
	//initialize arrays
	for(i = 0; i < NUMNODES + 1; i++)
	{
		nodeList[i] = 0;
		nodeSet[i] = -1;
	}
	
	while(!finFlag)
	{
		minConnections = NUMNODES + 1;		//reset minConnections to value larger than possible
		
		//find a valid node with the least amount of meaningful connections
		for(i = 0; i < NUMNODES; i++)
		{
			if(nodeList[i] == 0)		//only check nodes that are   1: not already selected   and   2: not adjacent to a selected node
			{
				numConnections = 0;
				for(j = 0; j < NUMNODES; j++)	//step through each possible connection
				{
					if(matrix[i][j] == 1 && nodeList[j] == 0)	//check if a connection exists and if the connected node is not adjacent to another node
					{
						numConnections++;
					}
				}
				
				//update the minimum node
				if(numConnections < minConnections)
				{
					minConnections = numConnections;
					minNode = i;
				}
			}
		}
		
		//add the minimum node to the set
		nodeSet[nodeCount] = minNode;
		nodeCount++;
		
		//update the node list to show which nodes are in the set, and which nodes are adjacent
		nodeList[minNode] = 1;
		for(i = 0; i < NUMNODES; i++)
		{
			if(matrix[minNode][i] == 1)
			{
				nodeList[i] = 2;
			}
		}
		
		//end the loop if every node in the nodeList is accounted for
		finFlag = true;
		for(i = 0; i < NUMNODES; i++)
		{
			if(nodeList[i] == 0)
			{
				finFlag = false;
			}
		}
	}
	
	nodeSet[NUMNODES] = nodeCount;			//store set size in last element
	return nodeSet;
}

Graph::~Graph()
{
}





