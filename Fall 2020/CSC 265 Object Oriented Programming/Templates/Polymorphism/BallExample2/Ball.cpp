// Polymorphism Example with no comments

#include <iostream>
#include "ball.h"

using namespace std;

void Ball::print() const
{	
	cout << "This is a generic ball." << endl;
}

void Baseball::print() const
{	
	cout << "This is a baseball." << endl;
}

void Football::print() const
{	
	cout << "This is a football." << endl;
}

void Basketball::print() const
{	
	cout << "This is a basketball." << endl;
}
