// Name
// Date
// CSC 265
// This program demonstrates a template function definition

#include <iostream>
using namespace std;

template <class T>
T smaller(T number1, T number2);
// Purpose:        Find the smaller of two values
// Preconditions:  Pass in two valid values
// Postconditions: The smaller of the two values is returned

int main(void)
{
  cout << "Smaller of 4 and 8 is: " << smaller(4, 8) << endl;
  cout << "Smaller of 7.6 and 4.5 is: " << smaller(7.6, 4.5) << endl;
  
  system("pause");
  return 0;
}

template <class T>
T smaller(T number1, T number2)
{
  T answer = number2;
  
  if(number1 < number2)
    answer = number1;
  
  return answer;
}
