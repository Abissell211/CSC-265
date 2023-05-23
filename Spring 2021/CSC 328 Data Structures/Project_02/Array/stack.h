// Andrew Bissell, Andrew Spate, Nicholas Spudich, and Zachary Wright

/*

//--------------------Constructor--------------------\\
FUNCTION:        Set();
General            : Initializes the values for the constructor
Preconditions    : Private data needs to be set: Top, IntStack[SIZE]
PostConditions    : Constructor initializes private data with a value of -1.
/

//--------------------Deconstructor------------------\\
FUNCTION:        ~Set();
General            : Deconstructor made to destroy the list once return 0 is given in main.
Preconditions    : Needs a list created and uses private data Top, IntStack[SIZE]
PostConditions    : The Array holding the linked list is deleted.
/

//--------------------Class Functions----------------\\
FUNCTION:        Push
General            : Pushes a new node onto the stack.
Preconditions    : Use of the Private data Top and IntStack[]
PostConditions    : Adds a node to the linked list and puts the data inputed by the user into the node.
/

/
FUNCTION:        Pop
General            : Pops a node from the top of the stack.
Preconditions    : Use of the Private data Top and IntStack[] and a Temp variable.
PostConditions    : Deletes the top data in the stack and decrements Top once.
/

/
FUNCTION:        StackTop
General            : Shows the top of the stack
Preconditions    : Use of the Private data Top and IntStack[] and a Temp variable.
PostConditions    : returns the value of the top of the stack with the use of a temp variable.
/

/
FUNCTION:        Display
General            : Displays the Stack
Preconditions    : Use of the Private data Top and IntStack[] and a Temp variable
PostConditions    : Will display the entire stack from Top to bottom
*/


#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <iomanip>

const int SIZE = 8;

struct Node
{
	int Num;
	struct Node* Next;
};


class Stack
{
	public:
		Stack();
		~Stack();
		void Push(int Num);
		int Pop();
		int StackTop();
		void Display();

	private:
		int Top;
		int IntStack[SIZE];

};

#endif
