#include "Car.h"

using namespace std;

Car::Car()
{
	make = "Honda";
}

void Car::setmake(string temp)
{	
	int len1 = 3;
	
	while (!(cin >> temp) || cin.peek() !=  '\n' || len1 > temp.size()){
		cout << "Please input a make more than three characters." << endl;
		cin.clear();
		cin.ignore(30000,'\n');
	}
	make = temp;
}

string Car::getmake(void) const
{
	return make;
}

void Car::display(void) const
{
	cout << "The make of the car is: " << getmake() << endl;
}
