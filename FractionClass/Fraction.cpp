#include <iostream>
#include "fraction.h"

using namespace std;

// CONSTRUCTOR
Fraction::Fraction()
{
  sign = '+';
  whole = 0;
  num = 0;
  den = 1;
}


// MODIFICATION MEMBER FUNCTIONS
void Fraction::setsign(const char value)
{
  if(value == '+' || value == '-')
    sign = value;
}


void Fraction::setwhole(const int value)
{
  if(value >= 0)
    whole = value;
}


void Fraction::setnum(const int value)
{
  if(value >= 0)
    num = value;
}


void Fraction::setden(const int value)
{
  if(value > 0)
    den = value;
}


// CONSTANT MEMBER FUNCTIONS
char Fraction::getsign(void) const
{
  return sign;
}


int Fraction::getwhole(void) const
{
  return whole;
}


int Fraction::getnum(void) const
{
  return num;
}


int Fraction::getden(void) const
{
  return den;
}


void Fraction::display(void) const
{
  if(whole == 0 && num == 0)
    cout << 0;
  else
  {
    if(sign == '-')
      cout << "-";

    if(num == 0)
      cout << whole;
    else if(whole == 0)
      cout << num << "/" << den;
    else
      cout << whole << " " << num << "/" << den;
  }
}
