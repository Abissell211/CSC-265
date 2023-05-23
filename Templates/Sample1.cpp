// Name
// Date
// CSC 265
// This program demonstrates overloaded functions

#include <iostream>
using namespace std;

int min(int, int);
// Purpose:        Find the smaller of two integer values
// Preconditions:  Pass in two valid integer values
// Postconditions: The smaller of the two values is returned

double min(double, double);
// Purpose:        Find the smaller of two double values
// Preconditions:  Pass in two valid double values
// Postconditions: The smaller of the two values is returned


int main(void)
{
  cout << "Min of 4 and 8 is: " << min(4, 8) << endl;
  cout << "Min of 7.6 and 4.5 is: " << min(7.6, 4.5) << endl;

  // Signal that program ended successfully
  system("pause");
  return 0;
}

int min(int number1, int number2)
{
  int answer = 0;
  
  cout << "Look, I'm working with integers!" << endl;
  if(number1 < number2)
    answer = number1;
  else
    answer = number2;
    
  return answer;
}

double min(double number1, double number2)
{
  double answer = 0.0;
  
  cout << "Look, I'm working with doubles!" << endl;
  if(number1 < number2)
    answer = number1;
  else
    answer = number2;
    
  return answer;
}
