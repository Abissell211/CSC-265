#include <iostream>
#include "Graph.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv)
{
	int * MIS;
	int i;
	time_t t, tt;
	char C;
	
	//create and print graph
	Graph G;
	G.printGraph();
	
	
	//find Maximum independ set using brute force approach
	t = time(0);
	MIS = G.brute();
	tt = time(0);
	
	//print time taken
	cout << endl << "Time taken for brute force approach: ";
	if(tt - t == 0)
	{
		cout << "less than a second" << endl;
	}
	else
	{
		cout << tt-t << " seconds" << endl;
	}
	
	//print the maximum independent set
	cout << "Maximum Independent Set: ";
	for(i = 0; i < G.getNumNodes(); i++)
	{
		if(*(MIS + i) != -1)
		{
			cout << *(MIS + i) << " ";
		}
	}
	cout << endl << "Size of the set: " << *(MIS + G.getNumNodes()) << endl << endl;		//prints the set size
	
	
	
	//find maximum independent set approximation using greedy approach
	t = time(0);
	MIS = G.greedy();
	tt = time(0);
	
	//print time taken
	cout << endl << "Time taken for greedy approximation: ";
	if(tt - t == 0)
	{
		cout << "less than a second" << endl;
	}
	else
	{
		cout << tt-t << " seconds" << endl;
	}
	
	//print results of approximation
	cout << "Approximated Maximum Independent Set: ";
	for(i = 0; i < G.getNumNodes(); i++)
	{
		if(*(MIS + i) != -1)
		{
			cout << *(MIS + i) << " ";
		}
	}
	cout << endl << "Size of the set: " << *(MIS + G.getNumNodes()) << endl << endl;		//prints the set size
	
	
	//this loop is to make sure we don't exit the results screen by accidently clicking a key, don't want to waste 24 hours of processing time
	do
	{
		cout << "Enter 'Q' to quit: ";
		cin >> C;
	}while(C != 'Q');
	
	return 0;
}
