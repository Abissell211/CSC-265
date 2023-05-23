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
	Temp = new Node;						// Creates new node using Temp
	if(!Temp)								
	{
		cout << "Stack is full!" << endl;	// Display to user
		exit(1);							// Exits function
	}
	else
	{
			Temp -> Num = Num; 						// Create space for Temp
			Temp -> Next = Top;						// Put ptr in temp
			Top = Temp; 							// Temp becomes top of stack
	}
}

int Stack::Pop()
{
	if (Top == 0)							// If Top is empty...
	{
		cout << "Stack is empty" << endl;	// Display to user
		exit(1);							// Exits function
	}
	else
	{
		int x = Top -> Num;					// store top num
		Temp = Top;							// Temp equals Top
		Top = Top -> Next;					// Top moves to next node
		Temp -> Num = 0; 					// remove first points to second
		delete Temp;							// remove node
		return x;							// return popped value
	}
}

int Stack::Peek()
{
	if(Top != 0)							// If Top is not empty
		return Top -> Num;					// Return the value of Top
	else
		return -1;							// Exits function
}

void Stack::Clear()							// Empties the stack
{
	while(Top != 0)
	{
		Temp = Top;
		Top = Top -> Next;
		Temp -> Num = 0;
		delete Temp;
	}
}

/*void Stack::Display()						// For Testing Purposes
{
	Temp = Top;
	cout << "Stack elements are: ";
	while (Temp != 0)
	{
		cout << Temp -> Num << " ";
		Temp = Temp -> Next;
	}
	cout << endl;
}*/
