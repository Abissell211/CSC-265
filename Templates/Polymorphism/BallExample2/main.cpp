// Polymorphism Example with no comments

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ball.h"

using namespace std;

const int SIZE = 5;

int main(void)
{
	Ball* ptr=0;
	int i = 0;
	
	srand(time(0));
	
	for(i = 0; i < SIZE; i++)
	{
		switch(rand() % 4 + 1)
		{
			case 1:					// Remove Lines 23 - 25 if you are using Ball as an abstract class, this will remove the generic ball so you only use class ball to create derived classes. 
				ptr = new Ball;
				break;
			case 2:
				ptr = new Baseball;
				break;
			case 3:
				ptr = new Football;
				break;
			case 4:
				ptr = new Basketball;
				break;
		}
		
		ptr -> print();
		delete ptr;
	}
	
    system("PAUSE");
	return 0;
}


// Example of how abstract classes could be used. 
// ZOO Program
	// Base Class Animal			(abstract class)
		// Derived Class Reptile		(abstract class)
			// Derived Class Gecio			(class)
			// Derived Class Cobra			(class
		// Derived Class Mammal			(abstract class)
			// Derived Class Monkey			(class)
			// Derived Class Deer			(class)
		// Derived Class Amphibian		(abstract class)
			// Derived Class Frog			(class)
