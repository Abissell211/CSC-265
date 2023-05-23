#include "stack.h"
#include <iostream>
#include <cstdlib>

using namespace std;


/*===========================
	Set Constructor
===========================*/
Stack::Stack()
{
	Top = 0;								// Initialize the Top of the stack
	Temp = 0;								// Initialize the Temp element
}

Stack::~Stack()
{
	Temp = Top;								// Temp equals Top
	while(Top != 0)							// While top doesn't equal to zero...
	{
		Temp = Top -> Next;					// Make the next from top is temp
		delete Top;							// Delete top
		Top = Temp;							// Top equals Temp
	}	
	
}

void Stack::Push(int Num)
{
	Temp = new Node();						// Creates new node using Temp
	
	if(!Temp)								
	{
		cout << "Stack is full!" << endl;	// Display to user
		exit(1);							// Exits function
	}
	
	Temp -> Num = Num; 						// Create space for Temp
	Temp -> Next = Top;						// Put ptr in temp
	
	Top = Temp; 							// Temp becomes top of stack
}

void Stack::Pop()
{	
	if (Top == 0)							// If Top is empty...
	{
		cout << "Stack is empty" << endl;	// Display to user
		exit(1);							// Exits function
	}
	else
	{
		Temp = Top;							// Temp equals Top
		Top = Top -> Next;					// Top moves to next node
		Temp -> Num = 0; 					// remove first points to second
		free(Temp); 						// remove top node
	}
}

int Stack::Peek()
{
	if(Top != 0)							// If Top is not empty
		return Top -> Num;					// Return the value of Top
	else
		exit(1);							// Exits function
}

