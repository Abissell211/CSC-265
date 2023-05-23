#include <iostream>
#include <cstring>
#include <functional>
#include <cstdlib>
#include <stdio.h>

using namespace std;

#ifndef CAR_H
#define CAR_H

class Car
{
	public:
		Car();
		
		void setmake(string);
		
		string getmake(void) const;
		void display(void) const;
		
	private:
		string make;
		
};

#endif

