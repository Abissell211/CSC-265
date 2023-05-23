#include <iostream>	// std::cout, endl
#include <string>	// string processing
#include "stack.h"	// includes information from header file

using namespace std; // scope for identifiers 

int main() 
{
	Stack s; // inherit stack class; creating object s
	
	s.Push(5); // push to stack
	s.Push(35);
	s.Push(15);
	s.Push(17);
	s.Push(5);
	s.Push(28);
	s.Push(55);
	s.Push(1000);
	s.Push(78); // stack is full; error 78 not added

	s.Display(); // prints stack from top to last

	cout << "\nTop element is: " << s.StackTop() << endl; // print top element of stack; using stack top to peek
	
	s.Pop(); // remove top element of stack
	s.Display(); 
	
	cout << "\nTop element is: " << s.StackTop() << endl;
	
	return 0;
}
