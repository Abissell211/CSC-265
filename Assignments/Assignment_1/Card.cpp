#include "Card.h"

using namespace std;

//-------------------------------------CLASS CARD--------------------------------------

// CONSTRUCTOR
Card::Card()
{
	num = 1;
	suit = "red";
}

//OVERLOADED CONSTRUCTOR
Card::Card(int number, string suit1){
	num = number;
	suit = suit1;
	
}

// MODIFICATION MEMBER FUNCTIONS
void Card::setsuit(string value)
{
	if(value == "red" || value == "white" || value == "blue")
		suit = value;
}

void Card::setnum(int value)
{
  	if(value > 0 && value <= 10)
    	num = value;
}

// CONSTANT MEMBER FUNCTIONS
string Card::getsuit(void) const 
{
  	return suit;
}

int Card::getnum(void) const
{
  	return num;
}

void Card::display() const
{
	cout << " " << num << " " << "of" << " " << suit << " ";
}

// ------------------------------------CLASS DECK-------------------------------------

// CONSTRUCTOR
Deck::Deck()
{	
	int i;
	
	for(i = 0; i < 10; i++)
	{
		deck[i].setnum(i+1);
		deck[i].setsuit("red");

	}
	
	for(i = 10; i < 20; i++)
	{
		deck[i].setnum(i-9);
		deck[i].setsuit("white");

	}
	
	for(i = 20; i < 30; i++)
	{
		deck[i].setnum(i-19);
		deck[i].setsuit("blue");

	}
}

// MODIFICATION MEMBER FUNCTIONS
void Deck::shuffle()
{
	int num1, num2, num3, num4;
	
	srand(time(0));
	
	for(int i = 0; i <= 1000; i++){
		num1 = rand() % 30;
		num2 = rand() % 30;
		num3 = rand() % 30;
		num4 = rand() % 30;
		swap(deck[num1], deck[num2]);
		swap(deck[num3], deck[num4]);
		swap(deck[num1], deck[num4]);
		swap(deck[num2], deck[num3]);	
	}
}

// CONSTANT MEMBER FUNCTIONS
Card Deck::getacard(const int slot)
{
	return deck[slot];
}

void Deck::display()
{
	for(int i = 0; i < SIZE; i++)
		deck[i].display();
}
