// CLASS PROVIDED:  Card
//
// CONSTRUCTOR for the Card class:
//   Card()
//     Description:		constructor will initialize Card objects
//     Preconditions:	none
//     Postcondition:	Card has been set to number(int) then suit(string)
//
//   Card(int, string)
//     Description:		overload constructor will initialize Card objects
//     Preconditions:	none
//     Postcondition:	Card has been set to number(int) then suit(string)
//
// MODIFICATION MEMBER FUNCTIONS for the Card class
//   void setsuit (const char value)
//     Description:		set the suit of the card
//     Precondition:	value is 'red', 'white', or 'blue' 
//     Postcondition:	suit of the card has been set to value
//
//   void setnum(const int value)
//     Description:		set the number to the Card
//     Precondition:	value is a non-negative value one through 10
//     Postcondition:	number part of the card is set to value
//
// CONSTANT MEMBER FUNCTIONS for the Card class
//   char getsuit (void) const
//     Description:		obtain suit of the card
//     Preconditions:	none
//     Postcondition:	suit of the card is returned
//
//   int  getnum(void) const
//     Description:		obtain number part of the card
//     Preconditions:	none
//     Postcondition:	number part of the card is returned
//
//   void display (void) const
//     Description:		display card to the screen
//     Preconditions:	none
//     Postcondition:	value of the card is displayed on the screen
//
// CONSTRUCTOR for the Deck class:
//   Deck()
//     Description:		constructor will initialize Deck Objects
//     Preconditions:	Class Card needed to set deck to set a int and string to one
//						array slot that matches the values of Class Card.
//     Postcondition:	The Deck has been set to three suits with 10 numbers in each
//						array slot.
// MODIFICATION MEMBER FUNCTIONS for the Deck class
//   void shuffle();
//     Description:		Using a new seed each time function is called to shuffle a
//						a deck.
//     Precondition:	none 
//     Postcondition:	using 4 variables to swap the locations within the deck's array,
//						the deck's array will be thoroughly shuffled.
// CONSTANT MEMBER FUNCTIONS for the Card class
//   Card getacard(const int)
//     Description:		Obtains a card from the shuffled deck. 
//     Preconditions:	none
//     Postcondition:	Returns a value from a deck.
//
//   void display (void);
//     Description:		Displays a decks values 
//     Preconditions:	none
//     Postcondition:	Displayes the deck num and suit values for each array slot.
#include <iostream>
#include <string>
#include <functional>
#include <cstdlib>
#include <time.h>

using namespace std;

#ifndef CARD_H
#define CARD_H

const int SIZE = 30;

class Card
{
  	public:
    	// CONSTRUCTOR
    	Card();
    	
    	//OVERLOAD CONSTRUCTOR
    	Card(int, string);

    	// MODIFICATION MEMBER FUNCTIONS
    	void setsuit(string);
    	void setnum(int);

    	// CONSTANT MEMBER FUNCTIONS
		string getsuit (void) const;
    	int  getnum  (void) const;
    	void display (void) const;
    
	private:
  		int num;
    	string suit;
};

class Deck
{
	public:
		// CONSTRUCTOR
		Deck();
		
		// MODIFICATION MEMBER FUNCTIONS
		void shuffle();
		
		// CONSTANT MEMBER FUNCTIONS
		Card getacard(const int);
		void display (void);
				
	private:
		Card deck[SIZE];	
		
};
#endif
