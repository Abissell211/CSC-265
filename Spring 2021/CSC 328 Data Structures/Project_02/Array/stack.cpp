#include "stack.h"
#include <iostream>

using namespace std;

/*===========================
	Set Constructor
===========================*/
Stack::Stack()
{
	Top = -1;											// initialize the top of the stack
	IntStack[-1];										// initialize the stack element
}

Stack::~Stack()
{
	delete []IntStack;									// delete the array the stack was located in 
}

void Stack::Push(int Num)
{
	if(Top == SIZE - 1)									// if the top is equal to the size -1
		cout << "Error, stack is full! Number " << Num << " was not added to stack!" << endl;		// error message
	else
	{
		Top++;											// step the top position 
		IntStack[Top] = Num;							// set the next number equal to the input number
	}
}


int Stack::Pop()
{
	int Temp = 0;										// set an temp placeholder value

	if(Top == -1)										// if top location is equal to the initialization value
		cout << "Error, stack is empty!" << endl;		// error message
	else
	{
		Temp = IntStack[Top];							// set the temp equal to the top
		Top--;											// step the top back
	}
	
	return Temp;
}


int Stack::StackTop()
{
	int Temp = 0;
	
	if(Top == -1)										// if top is equal to initialization value
		cout << "Error, Stack is empty!" << endl;		// error message
	else
		Temp = IntStack[Top];							// set temp equal to the top position
	
	return Temp;
}


void Stack::Display()
{
	int Temp;
	Temp = Top;
	if(Top == -1)										// if top is in th einitialization position
	{
		cout << "Stack is empty!" << endl;				// message
		exit(1);
	}
	else
	{
	while(Temp != -1)									// while the temp value is the initialized value
		{
		cout << IntStack[Temp] << endl;					// print the value in the stack
		Temp -= 1;										// step the list to the next value
		}
	}

}

