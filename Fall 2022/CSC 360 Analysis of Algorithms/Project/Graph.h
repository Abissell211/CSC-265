#define NUMNODES 1
#define EDGEDENSITY 50

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Graph
{
	private:
		int matrix[NUMNODES][NUMNODES];
		int nodeList[NUMNODES + 1];		//array to hold each combination of nodes, last index is the control field
		int nodeSet[NUMNODES + 1];		//the maximum independent set, last index is the size of the set
	public:
		Graph();
		//Description: 		constructor, creates adjacency matrix
		//Preconditions: 	class unconstructed
		//Postconditions: 	class constructed, adjacency matrix filled correctly according to number of nodes and edge density
		
		void printGraph();
		//Description: 		prints graph
		//Preconditions: 	adjacency matrix is filled correctly
		//Postconditions: 	each node is printed, along with the list of nodes adjacent to it
		
		int getNumNodes();
		//Description: 		get number of nodes in graph
		//Preconditions: 	NUMNODES is defined
		//Postconditions: 	returns NUMNODES constant
		
		int * brute();
		//Description: 		calculate maximum independ set by trying every possibility
		//Preconditions: 	adjacency matrix is filled correctly
		//Postconditions:	returns a pointer to the array filled with the maximum independent set, last index of that array is the size of the set	
		
		int * greedy();	
		
		~Graph();
		//Description:		deconstructor
		//Preconditions:	class constructed
		//Postconditions:	class destructed
	protected:
};

#endif
