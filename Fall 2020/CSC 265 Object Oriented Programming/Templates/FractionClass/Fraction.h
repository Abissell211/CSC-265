// CLASS PROVIDED:  Fraction (an ADT for a fraction)
//
// CONSTRUCTOR for the Fraction class:
//   Fraction()
//     Description:		constructor will initialize Fraction objects
//     Preconditions:	none
//     Postcondition:	fraction has been set to +0 0/1
//
// MODIFICATION MEMBER FUNCTIONS for the Fraction class
//   void setsign (const char value)
//     Description:		set the sign of the fraction
//     Precondition:	value is either '+' or '-'
//     Postcondition:	sign of the fraction has been set to value
//
//   void setwhole(const int value)
//     Description:		set the whole part of the fraction
//     Precondition:	value is a non-negative value
//     Postcondition:	whole part of the fraction has been set to value
//
//   void setnum  (const int value)
//     Description:		set the numerator of the fraction
//     Precondition:	value is a non-negative value
//     Postcondition:	numerator of the fraction has been set to value
//
//   void setden  (const int value)
//     Description:		set the denominator of the fraction
//     Precondition:	value is a positive value
//     Postcondition:	denominator of the fraction has been set to value
//
// CONSTANT MEMBER FUNCTIONS for the Fraction class
//   char getsign (void) const
//     Description:		obtain sign of the fraction
//     Preconditions:	none
//     Postcondition:	sign of the fraction is returned
//
//   int  getwhole(void) const
//     Description:		obtain whole part of the fraction
//     Preconditions:	none
//     Postcondition:	whole part of the fraction is returned
//
//   int  getnum  (void) const
//     Description:		obtain numerator of the fraction
//     Preconditions:	none
//     Postcondition:	numerator of the fraction is returned
//
//   int  getden  (void) const
//     Description:		obtain denominator of the fraction
//     Preconditions:	none
//     Postcondition:	denominator of the fraction is returned
//
//   void display (void) const
//     Description:		display fraction to the screen
//     Preconditions:	none
//     Postcondition:	value of the fraction is displayed on the screen

#ifndef FRACTION_H
#define FRACTION_H

class Fraction
{
  public:
    // CONSTRUCTOR
    Fraction();

    // MODIFICATION MEMBER FUNCTIONS
    void setsign (const char);
    void setwhole(const int);
    void setnum  (const int);
    void setden  (const int);

    // CONSTANT MEMBER FUNCTIONS
    char getsign (void) const;
    int  getwhole(void) const;
    int  getnum  (void) const;
    int  getden  (void) const;
    void display (void) const;

  private:
    char sign;
    int  whole;
    int  num;
    int  den;
};

#endif
