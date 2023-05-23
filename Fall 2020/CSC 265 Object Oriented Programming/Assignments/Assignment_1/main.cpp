// Andrew D. Bissell
// Charles Krug
// Patrick Barker
#include <iostream>
#include <cstdlib>
#include <string>
#include "Card.h"

using namespace std;

	int compfollow(Card player[], Card comp1[], Card comp2[], int cardcount); // Starts line 133.
	int comp1start(Card player[], Card comp1[], Card comp2[], int cardcount); // Starts line 510
	int comp2start(Card player[], Card comp1[], Card comp2[], int cardcount); // Starts line 886

int main(void)
{
	cout << " Welcome to my card game program. Press any key to draw your deck after you look\n" <<
		"at your cards bet on how many tricks you will win. To win a trick you have to play\n" <<
		"the highest face value of the suit that has already been played. You get to start\n" <<
		"the first round and who ever wins plays the first card of the next round. The game\n" <<
		"end when either you or your computer opponents get 100 points, you get points if\n" <<
		"you make your bet (10 points per rounds won with bet achived) computers will win\n" <<
		"10 points per round win they do not bet! GOOD LUCK!\n" << endl;
		
	system("Pause");
	cout << endl;
	
	int bet, trickswon;										// Number of tricks bet and won by player.
	int playerscore = 0, comp1score = 0, comp2score = 0;	// Scores for all three players.
	int cardcount = 10;										// A count on what cards we have for the round.
	int turn;												// A variable for whos turn.
	int playerturn = 1, comp1turn = 2, comp2turn = 3;		// A variable for each players turn designator.
	
	while(playerscore < 100 && comp1score < 100 && comp2score < 100){	// Loop for player/computer victory.
	
	Deck deckofcards;							// Deck of 30 Cards.
	Card player[10];							// player deck of 10 cards.
	Card comp1[10];								// comp1 deck of 10 cards.
	Card comp2[10];								// comp2 deck of 10 cards. 
	deckofcards.shuffle();						// Deck Class function to shuffle deckofcards.
	
	for(int i = 0; i < cardcount; i++){				// Loop to get 10 cards for player from deckofcards, 
		player[i] = deckofcards.getacard(i);	// and display the 10 cards to the user. 
		player[i].display();					// --TEST-- This is to check the player hand.
	}
		cout << endl;
		
		for(int i = 0; i < cardcount; i++){			// Loop to get 10 cards for comp1 from deckofcards
		comp1[i] = deckofcards.getacard(i+10);
		//comp1[i].display();						// --TEST-- This is to check the comp1 hand.
	}
		//cout << endl;							// --TEST--
		
		for(int i = 0; i < cardcount; i++){			// Loop to get 10 cards for comp2 from deckofcards
		comp2[i] = deckofcards.getacard(i+20);
		//comp2[i].display();						// --TEST-- This is to check the comp2 hand.
	}
		//cout << endl;							// --TEST--
	
	cout << "\n" << "Bet how many tricks you will win(1 - 10): ";	// Announcement to user.
	cin >> bet;												// User input for bet. 
	
	while(bet > 10 || bet <= 0){								// While loop to check if user inputs
		cin.clear();											// correct value for bet.
		cout << "Please enter a whole number 1 - 10." << endl;	// Error message for user.
		cin >> bet;												// Re-input for bet
	}

	cout << "You bet: " << bet << " tricks" << "\n" << endl;			// Display the bet entered by the user to the user
	
	
	int temp = compfollow(player ,comp1, comp2, cardcount);				// Temp will be whatever the outcome of compfollow this is also the first trick out of 10.
	
	for(cardcount = 9; cardcount >= 1; cardcount--){					// Loop for the last 9 cards (last 9 tricks)	
			if(temp == 1){
				trickswon += 1;												// Checks to see if player won last trick.
				cout << "\nPlayer's wins: " << trickswon << "		Computer 1 score: " << comp1score << " 		Computer 2 score: " << comp2score << endl;
				temp = compfollow(player, comp1, comp2, cardcount);		// Assigns the value returned by compfollow to temp.
				}
			else
				if(temp == 2 ){	
					comp1score += 10;										// Checks to see if computer 1 won last trick.
					cout << "\nPlayer's wins: " << trickswon << " 	Computer 1 score: " << comp1score << " 		Computer 2 score: " << comp2score << endl;
					temp = comp1start(player, comp1, comp2, cardcount);	// Assigns the value returned by comp1start to temp.
				}
				else{
					comp2score += 10;													// If computer 1 didn't win then computer 2 must of won.
					cout << "\nPlayer's wins: " << trickswon << " 	Computer 1 score: " << comp1score << " 		Computer 2 score: " << comp2score << endl;
					temp = comp2start(player, comp1, comp2, cardcount);	// Assigns the value returned by comp2start to temp.
					}
				}
				
	if(temp == 1){			// Adds the trick won to player if player wins last round.
		trickswon +=1;	
	}
	if(temp == 2){				// Adds last 10 points if comp1 won last round. 
		comp1score += 10;
	}
	if(temp == 3){				// Adds last 10 points if comp2 won last round. 
		comp2score += 10;
	}
	
	if(trickswon >= bet){			// Checks if player won their bet.
		playerscore += bet * 10;	// Adds bet won to their overall score. 
		trickswon = 0;				// Reset variable.
		bet = 0;					// Reset variable. 
	}
	else{
		playerscore -= bet * 10;	// Subtracts bet won from their overall score. 
		trickswon = 0;				// Reset variable.
		bet = 0;					// Reset variable.
	}
	cout << "Your score is: " << playerscore << endl;	// Shows the player their score after the full 10 tricks are over. 
	
	cardcount = 10;		// Reset variable.
	
}

if(playerscore >= 100 && playerscore >= comp1score && playerscore >= comp2score){	// Check to see if player won.
	cout << "Player wins with " << playerscore << "points!" << endl;				// Announces player wins to user.
}
if(comp1score >= 100 && comp1score >= playerscore && comp1score >= comp2score){		// Check to see if comp1 won.
	cout << "Computer 1 wins with " << comp1score << "points!" << endl;				// Announces computer 1 wins to user.
}
if(comp2score >= 100 && comp2score >= playerscore && comp2score >= comp1score){		// Check to see if comp2 won.
	cout << "Computer 2 wins with " << comp2score << "points!" << endl;				// Announces computer 2 wins to user.
}

return 0;

}

int comp1start(Card player[], Card comp1[], Card comp2[], int cardcount){		// Function where comp1 starts.
	
	int playercard = 0, comp1card = 0, comp2card = 0; 	// Player and computers cards played in trick.
	int comp1red = 0, comp1white = 0, comp1blue = 0;	// Count for each suit the comp1 has in hand.
	int comp2red = 0, comp2white = 0, comp2blue = 0; 	// Count for each suit the comp2 has in hand.
	int comp1rand = 0;									// Random number to get random suit.
	string comp1suit = "";								// Assign suit to variable to check.
	int comp1high = 0, comp2high = 0;					// Computer 1 and 2's highest numbered card in deck.
	int comp1low = 0, comp2low = 0;						// Computer 1 and 2's lowest numbered card in deck.
	
		for(int i = 0; i < cardcount; i++){															// Loop to check how many cards of each suit within computer 1's hand.
		if(comp1[i].getsuit() == "red"){
			comp1red += 1;																			// Comp1's number of red cards.
		}
		if(comp1[i].getsuit() == "white"){
			comp1white += 1;																		// Comp1's number of white cards
		}
		if(comp1[i].getsuit() == "blue"){
			comp1blue += 1;																			// Comp1's number of blue cards.
		}
	}
	// cout << comp1red << " red\n"<< comp1white << " white\n" << comp1blue << " blue" << endl;		// --TEST-- Check to see if the correct values are displayed.
	
	for(int i = 0; i < cardcount; i++){																// Loop to check how many cards of each suit within computer 2's hand.
		if(comp2[i].getsuit() == "red"){
			comp2red += 1;																			// Comp2's number of red cards.
		}
		if(comp2[i].getsuit() == "white"){
			comp2white += 1;																		// Comp2's number of white cards.
		}
		if(comp2[i].getsuit() == "blue"){
			comp2blue += 1;																			// Comp2's number of blue cards.
		}
	}
	// cout << comp2red << " red\n"<< comp2white << " white\n" << comp2blue << " blue" << endl;		// --TEST-- Check to see if the correct values are displayed.
	
	srand(time(0));	
	comp1rand = rand() % 3 + 1;							// Random number 1-3 to choose a suit.
		
	if(comp1rand == 1){
		comp1suit = "red";								// comp1suit selected is red. 
	}
	if(comp1rand == 2){
		comp1suit = "white";							// comp1suit selected is white. 
	}
	if(comp1rand == 3){
		comp1suit = "blue";								// comp1suit selected is blue.
	}
	
	// cout << comp1rand << endl;																		// --TEST-- for random suit.
//-----------------------------------------------------------------COMP1's TURN--------------------------------------------------------------------------------------------------//	
	if(comp1suit == "red"){																			// Checks to see if comp1 choose red.
		if(comp1red > 1){																			// Checks to see if comp1 has a red suit. 
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "red"){				// Tests to see if comp1's hand has a greatest value of suit red.
						comp1high = comp1[i].getnum();
						comp1card = i;																
					}
				}
			}
		else
			if(comp1white > 1){																		// Checks to see if comp1 has a white suit. 
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "white"){				// Tests to see if comp1's hand has a highest value of suit white.
						comp1high = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
			else																					// If not red or white comp1 will use blue.
				for(int i = 0; i < cardcount; i++){										
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "blue"){				// Tests to see if comp1's hand has a highest value of suit blue.
						comp1high = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
		

	if(comp1suit == "white"){																		// Checks to see if comp1 choose white.
		if(comp1white > 1){																			// Checks to see if comp1 has a white suit.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "white"){				// Tests to see if comp1's hand has a highest value of suit white.
						comp1high = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
		else
			if(comp1blue > 1){																		// Checks to see if comp1 has a blue suit.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "blue"){				// Tests to see if comp1's hand has a highest value of suit blue.
						comp1high = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
			else
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "red"){				// Tests to see if comp1's hand has a highest value of suit red.
						comp1high = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
	
	if(comp1suit == "blue"){
		if(comp1blue > 1){
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "blue"){				// Tests to see if comp1's hand has a lowest value of suit blue.
						comp1high = comp1[i].getnum();
						comp1card = i;																// This sends the slot of card choosen to play.
					}
				}
			}
		else
			if(comp1red > 1){
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "red"){				// Tests to see if comp1's hand has a lowest value of suit blue.
						comp1high = comp1[i].getnum();
						comp1card = i;																// This sends the slot of card choosen to play.
					}
				}
			}
			else																					// If not blue or red comp1 will use blue.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() > comp1high && comp1[i].getsuit() == "white"){				// Tests to see if comp1's hand has a lowest value of suit blue.
						comp1high = comp1[i].getnum();
						comp1card = i;
					}
				}
			}

	cout << "Computer 1 plays the";		// Announcement to the player.
	comp1[comp1card].display();			// Comp1 card displayed
	cout << endl;
//-----------------------------------------------------------------COMP2's TURN--------------------------------------------------------------------------------------------------//	
	if(comp1[comp1card].getsuit() == "red"){	// checks comp1 suit.
		if(comp2red < 1){						// checks if comp2 had a red suit.
			if(comp2blue > comp2white){			// checks if blue suit is more the white.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "blue"){	// Gets the lowest blue suit. 
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
			else
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "white"){	// Gets the lowest white suit.
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
		else
			for(int i = 0; i < cardcount; i++){
				if(comp2[i].getnum() > comp1[comp1card].getnum() && comp2[i].getsuit() == "red"){	// Gets the highest red suit.
					comp2high = comp2[i].getnum();
					comp2card = i;
		}
					if(comp2high == 0){																// Checks if it doesn't have a higher card to play. 
						comp2low = comp1[comp1card].getnum();										// sets the comp2 lowest to comp1 card.
						for(int i = 0; i < cardcount; i++){
							if(comp2[i].getnum() < comp1[comp1card].getnum() && comp2[i].getnum() < comp2low && comp2[i].getsuit() == "red"){	// Gets the lowest red suit.
								comp2low = comp2[i].getnum();
								comp2card = i;
				}
			}
		}
	}
}
	comp2high = 0;		// Reset variable.
	comp2low = 0;		// Reset variable. 
	if(comp1[comp1card].getsuit() == "blue"){													// Checks if comp1 card is suit blue.
		if(comp2blue < 1){																		// Checks if comp2 has a blue suit.
			if(comp2red > comp2white){															// Checks if it has more red suit than white.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "red"){			// Gets the lowest red suit.
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
			else
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "white"){			// Gets the lowest white suit. 
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
		else
			for(int i = 0; i < cardcount; i++){
				if(comp2[i].getnum() > comp1[comp1card].getnum() && comp2[i].getsuit() == "blue"){	// Plays the highest blue card.
					comp2high = comp2[i].getnum();
					comp2card = i;
			}
					if(comp2high == 0){																// Checks if it doesn't have a higher card to play.
						comp2low = comp1[comp1card].getnum();										// sets comp2 low to comp1's card. 
						for(int i = 0; i < cardcount; i++){
							if(comp2[i].getnum() < comp1[comp1card].getnum() && comp2[i].getnum() < comp2low && comp2[i].getsuit() == "blue"){	// playes the lowest blue suit. 
								comp2low = comp2[i].getnum();
								comp2card = i;
				}
			}
		}
	}
}
	comp2high = 0;		// Reset variable.
	comp2low = 0;		// Reset variable. 
	if(comp1[comp1card].getsuit() == "white"){												// Checks if comp1's card is white suit.
		if(comp2white < 1){																	// Checks if comp2 has a white suit.
			if(comp2red > comp2blue){														// Checks if comp2 has more red suit than white.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "red"){		// Plays lowest red suit.
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
			else
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "blue"){		// Plays lowest blue suit.
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
		else
			for(int i = 0; i < cardcount; i++){
				if(comp2[i].getnum() > comp1[comp1card].getnum() && comp2[i].getsuit() == "white"){		// Gets highest white suit.
					comp2high = comp2[i].getnum();
					comp2card = i;
		}
				if(comp2high == 0){																												// Checks if they don't have a card higher that comp1's played card.
					comp2low = comp1[comp1card].getnum();																						// Sets comp2 low variable to comp1's played card. 
					for(int i = 0; i < cardcount; i++){
						if(comp2[i].getnum() < comp1[comp1card].getnum() && comp2[i].getnum() < comp2low && comp2[i].getsuit() == "white"){		// Gets lowest white suit.
							comp2low = comp2[i].getnum();
							comp2card = i;
				}
			}
		}
	}
}
	
	cout << "Computer 2 plays the";
	comp2[comp2card].display();
	cout << "\n" << endl;	
//-----------------------------------------------------------------Players TURN--------------------------------------------------------------------------------------------------//
	for(int i = 0; i < cardcount; i++){							// Loop to get 10 cards for player from deckofcards, 
		player[i].display();
	}
			
	cout << "\nPlease choose a card 1 through " << cardcount <<" to play: ";	// Announcement to the player.
	cin >> playercard;														// Card the player chose.
	
		while(playercard > cardcount  || playercard <= 0){		// While loop to check user inputs
		cin.clear();											
		cout << "Please choose a card you have." << endl;		// Error message for user.
		cin >> playercard;
	}
	
	playercard -= 1;											// Makes it so the array slot is the correct card the player selected (since 0-9 is the array, 1-10 input needs a minus 1)
	cout << "You chose the: ";	 								// Announcement to the player.
	player[playercard].display();								// Displays the user selected card to the player.
	cout << endl;	
	
	if(comp2[comp2card].getsuit() != comp1[comp1card].getsuit() && player[playercard].getsuit() != comp1[comp1card].getsuit()){	// If no suit is equal to comp1's played card.
			cout << "Computer 1 wins the trick!" << endl;		// Comp1 wins.
			swap(player[playercard], player[cardcount - 1]);	// Swaps player chosen card with last card for that round.
			swap(comp1[comp1card], comp1[cardcount - 1]);		// Swaps comp1 chosen card with last card for that round.
			swap(comp2[comp2card], comp2[cardcount - 1]);		// Swaps comp2 chosen card with last card for that round.
			cout << endl;
			system("Pause");
			return 2;												// Sends value to main to let it know comp1 won.
	}
	if(comp1[comp1card].getsuit() == player[playercard].getsuit() && comp1[comp1card].getsuit() == comp2[comp2card].getsuit()){	// Checks if all the suits for the played cards match.
		if(comp1[comp1card].getnum() > player[playercard].getnum() && comp1[comp1card].getnum() > comp2[comp2card].getnum()){ // Checks if comp1's card is the greatest.
			cout << "Computer 1 wins the trick!" << endl;			// comp1 wins.
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);
			cout << endl;
			system("Pause");						
			return 2;
		}
	}
	if(comp2[comp2card].getsuit() != comp1[comp1card].getsuit()){			// Checks if comp2 suit is not equal to comp1's.
		if(player[playercard].getsuit() == comp1[comp1card].getsuit()){		// Checks if players suit is equal to comp1's.
			if(player[playercard].getnum() > comp1[comp1card].getnum()){	// Checks if players card is higher than comp1's.
				cout << "Player wins the trick!" << endl;					// Player wins.
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 1;
			}
		}
	else{
		cout << "Computer 1 wins the trick!" << endl;						// Comp1 wins if the card doesn't match or isn't higher than player.
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 2;		
	}
}
	if(player[playercard].getsuit() != comp1[comp1card].getsuit()){			// Checks if player suit is not equal to comp1's.
		if(comp2[comp2card].getsuit() == comp1[comp1card].getsuit()){		// Checks if comp2 suit is equal to comp1's.
			if(comp2[comp2card].getnum() > comp1[comp1card].getnum()){		// Checks if comp2 card is higher than comp1's.
				cout << "Computer 2 wins the trick!" << endl;				// Comp2 wins.
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 3;
			}
		}
	else{																	// Comp1 wins if the card doesn't match or isn't higher than comp2.
		cout << "Computer 1 wins the trick!" << endl;
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 2;		
	}
}
	if(player[playercard].getsuit() != comp2[comp2card].getsuit()){			// Checks if player suit is not equal to comp2's.
		if(comp1[comp1card].getsuit() == comp2[comp2card].getsuit()){		// Checks if comp1 suit is equal to comp2's.
			if(comp1[comp1card].getnum() > comp2[comp2card].getnum()){		// Checks if comp1 card is higher than comp2's.
				cout << "Computer 1 wins the trick!" << endl;				// Comp1 wins.
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 2;
			}
		}
	else{																	// Comp2 wins if the card doesn't match or isn't higher than comp1's.
		cout << "Computer 2 wins the trick!" << endl;						
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 3;			
		}		
	}
	if(player[playercard].getsuit() == comp1[comp1card].getsuit() && player[playercard].getsuit() == comp2[comp2card].getsuit()){	// Checks if player's suit is the same as comp1 and comp2.
		if(player[playercard].getnum() > comp1[comp1card].getnum() && player[playercard].getnum() > comp2[comp2card].getnum()){		// Checks if player's card is higher than comp1 and comp2.
			cout << "Player wins the trick!" << endl;				// Player wins.
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);			
			return 1;
			cout << endl;
		}
	}
	if(comp2[comp2card].getsuit() == player[playercard].getsuit() && comp2[comp2card].getsuit() == comp1[comp1card].getsuit()){		// Checks if comp2's suit is the same as player and comp1.
		if(comp2[comp2card].getnum() > player[playercard].getnum() && comp2[comp2card].getnum() > comp1[comp1card].getnum()){		// Checks if comp2's card is higher than player and comp2.
			cout << "Computer 2 wins the trick!" << endl;			// Comp2 wins.
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);
			return 3;
			cout << endl;
		}
	}	
}

int comp2start(Card player[], Card comp1[], Card comp2[], int cardcount){

	int playercard = 0, comp1card = 0, comp2card = 0; 	// Player and computers cards played in trick.
	int comp1red = 0, comp1white = 0, comp1blue = 0;	// Count for each suit the comp1 has in hand.
	int comp2red = 0, comp2white = 0, comp2blue = 0; 	// Count for each suit the comp2 has in hand.
	int comp1rand = 0;									// Random number to get random suit.
	string comp1suit = "";								// Assign suit to variable to check.
	int comp1high = 0, comp2high = 0;					// Computer 1 and 2's highest numbered card in deck.
	int comp1low = 0, comp2low = 0;						// Computer 1 and 2's lowest numbered card in deck.
	
		for(int i = 0; i < cardcount; i++){															// Loop to check how many cards of each suit within computer 1's hand.
		if(comp1[i].getsuit() == "red"){
			comp1red += 1;																			// Comp1's number of red cards.
		}
		if(comp1[i].getsuit() == "white"){
			comp1white += 1;																		// Comp1's number of white cards
		}
		if(comp1[i].getsuit() == "blue"){
			comp1blue += 1;																			// Comp1's number of blue cards.
		}
	}
	// cout << comp1red << " red\n"<< comp1white << " white\n" << comp1blue << " blue" << endl;		// --TEST-- Check to see if the correct values are displayed.
	
	for(int i = 0; i < cardcount; i++){																// Loop to check how many cards of each suit within computer 2's hand.
		if(comp2[i].getsuit() == "red"){
			comp2red += 1;																			// Comp2's number of red cards.
		}
		if(comp2[i].getsuit() == "white"){
			comp2white += 1;																		// Comp2's number of white cards.
		}
		if(comp2[i].getsuit() == "blue"){
			comp2blue += 1;																			// Comp2's number of blue cards.
		}
	}
	// cout << comp2red << " red\n"<< comp2white << " white\n" << comp2blue << " blue" << endl;		// --TEST-- Check to see if the correct values are displayed.
	
	srand(time(0));	
	comp1rand = rand() % 3 + 1;				// Gets a random number 1-3 to set the suit to play by comp.
		
	if(comp1rand == 1){						// If random number is 1 suit red is selected.
		comp1suit = "red";
	}
	if(comp1rand == 2){						// If random number is 2 suit white is selected.
		comp1suit = "white";
	}
	if(comp1rand == 3){						// If random number is 3 suit blue is selected.
		comp1suit = "blue";
	}
	
	// cout << comp1rand << endl;																	// --TEST-- for random suit.
//-----------------------------------------------------------------COMP2's TURN--------------------------------------------------------------------------------------------------//		
	if(comp1suit == "red"){																			// If comps suit is red.
		if(comp2red > 1){																			// Checks if comp2 has suit red.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "red"){				// Tests to see if comp2's hand has a highest value of suit red.
						comp2high = comp2[i].getnum();
						comp2card = i;																
					}
				}
		}
		else
			if(comp2white > 1){																		// Checks if comp2 has suit white.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "white"){				// Tests to see if comp2's hand has a greatest value of suit white.
						comp2high = comp2[i].getnum();
						comp2card = i;															
					}
				}
		}
			else																					// If comp2 doesn't have red or white.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "blue"){				// Tests to see if comp2's hand has a greatest value of suit blue.
						comp2high = comp2[i].getnum();
						comp2card = i;															
					}
				}
		}

	if(comp1suit == "white"){																		// If comps suit is white.
		if(comp2white > 1){																			// Checks if comp2 has suit white.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "white"){				// Tests to see if comp2's hand has a greatest value of suit white.
						comp2high = comp2[i].getnum();
						comp2card = i;															
					}
				}
		}
		else
			if(comp1blue > 1){																		// Checks if comp2 has suit blue.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "blue"){				// Tests to see if comp2's hand has a greatest value of suit blue.
						comp2high = comp2[i].getnum();
						comp2card = i;															
					}
				}
		}
			else																					// If comp2 doesn't have a white or blue.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "red"){				// Tests to see if comp2's hand has a greatest value of suit red.
						comp2high = comp2[i].getnum();
						comp2card = i;															
					}
				}
		}

	if(comp1suit == "blue"){																		// If comps suit is blue.
		if(comp2blue > 1){																			// Checks if comp2 has suit blue.
				for(int i = 0; i < cardcount; i++){		
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "blue"){				// Tests to see if comp2's hand has a greatest value of suit blue.
						comp2high = comp2[i].getnum();
						comp2card = i;															
					}
				}
		}
		else						
			if(comp2red > 1){																		// Checks if comp2 has suit red.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "red"){				// Tests to see if comp2's hand has a greatest value of suit red.
						comp2high = comp2[i].getnum();
						comp2card = i;													
					}
				}
		}
			else																					// If comp2 doesnt have a blue or red.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() > comp2high && comp2[i].getsuit() == "white"){				// Tests to see if comp2's hand has a greatest value of suit white.
						comp2high = comp2[i].getnum();
						comp2card = i;															
					}
				}
		}

	cout << "Computer 2 plays the";
	comp2[comp2card].display();
	cout << endl;
//-----------------------------------------------------------------COMP1's TURN--------------------------------------------------------------------------------------------------//	
	if(comp2[comp2card].getsuit() == "red"){														// Test statement for if the comp2 chooses a red card. 
		if(comp1red < 1){																			// Checks to see if comp1 has and cards of red suit. 
			if(comp1blue > comp1white){																// If it doesn't have a red it chooses which suit has more cards. 
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "blue"){				// Tests to see if comp1's hand has a lowest value of suit blue.
						comp1low = comp1[i].getnum();
						comp1card = i;																
					}
				}
			}
			else																					// If blue is NOT greater than white.
				for(int i = 0; i < cardcount; i++){													
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "white"){				// Check if the suit matches white and what the lowest card value for that suit. 
						comp1low = comp1[i].getnum();							
						comp1card = i;															
					}
				}
			}
		else																						// Comp1 has a red suit card. 
			for(int i = 0; i < cardcount; i++){
				if(comp1[i].getnum() > comp2[comp2card].getnum() && comp1[i].getsuit() == "red"){	// Check if the suit matches red and what the highest card value for that suit.
					comp1high = comp1[i].getnum();
					comp1card = i;																
		}
					if(comp1high == 0){																// If there isn't a card higher than the highest possible card.
						comp1low = comp2[comp2card].getnum();										// Sets the comp2 card to this lowest var.
						for(int i = 0; i < cardcount; i++){
							if(comp1[i].getnum() < comp2[comp2card].getnum() && comp1[i].getnum() < comp1low && comp1[i].getsuit() == "red"){	// Check if the suit matches red and what the lowest card value for that suit and verses what is low in hand.
								comp1low = comp1[i].getnum();
								comp1card = i;														
				}
			}
		}
	}
}
	comp1high = 0;																					// Resets variable to zero.
	comp1low = 0;																					// Resets variable to zero.
	if(comp2[comp2card].getsuit() == "blue"){														// If comp2's card is suit blue.
		if(comp1blue < 1){																			// Checks if comp1 has suit blue
			if(comp1red > comp1white){																// Checks if it has more red than white suit.
				for(int i = 0; i < cardcount; i++){	
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "red"){				// Gets lowest card for suit red.
						comp1low = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
			else																					// Comp1 has more white than red.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "white"){				// Gets lowest card for suit white.
						comp1low = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
		else																						// Comp1 has a blue suit.
			for(int i = 0; i < cardcount; i++){
				if(comp1[i].getnum() > comp2[comp2card].getnum() && comp1[i].getsuit() == "blue"){	// Gets the highest card for suit blue.
					comp1high = comp1[i].getnum();
					comp1card = i;
			}
					if(comp1high == 0){																// If comp1 doesn't have a blue card higher than comp2.
						comp1low = comp2[comp2card].getnum();										// Sets the comp2's card to lowest value.
						for(int i = 0; i < cardcount; i++){
							if(comp1[i].getnum() < comp2[comp2card].getnum() && comp1[i].getnum() < comp1low && comp1[i].getsuit() == "blue"){  // Gets the lowest card for suit blue.
								comp1low = comp1[i].getnum();
								comp1card = i;
				}
			}
		}
	}
}
	comp1high = 0;				// Reset variable.
	comp1low = 0;				// Reset variable.
	if(comp2[comp2card].getsuit() == "white"){												// If comp2's card is white.
		if(comp1white < 1){																	// Checks if comp1 has a card suit white.
			if(comp1red > comp1blue){														// Checks if comp1 has more red than blue.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "red"){		// Gets lowest card of suit red.
						comp1low = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
			else																			// Comp1 has more blue cards than red.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "blue"){		// Gets lowest card of suit blue.
						comp1low = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
		else																				// Comp1 has a card of suit white.
			for(int i = 0; i < cardcount; i++){
				if(comp1[i].getnum() > comp2[comp2card].getnum() && comp1[i].getsuit() == "white"){		// Gets the highest card of suit white.
					comp1high = comp1[i].getnum();
					comp1card = i;
		}
				if(comp1high == 0){																		// If comp1 doesn't have a higher card than comp2.
					comp1low = comp2[comp2card].getnum();												// Sets comp2's card to lowest value variable.
					for(int i = 0; i < cardcount; i++){
						if(comp1[i].getnum() < comp2[comp2card].getnum() && comp1[i].getnum() < comp1low && comp1[i].getsuit() == "white"){		// Gets the lowest card of suit white.
							comp1low = comp1[i].getnum();	
							comp1card = i;
				}
			}
		}
	}
}
	
	cout << "Computer 1 plays the";		// Announcement to player.
	comp1[comp1card].display();			// Comp1's card played.
	cout << "\n" << endl;	
//-----------------------------------------------------------------PLAYERS's TURN--------------------------------------------------------------------------------------------------//	
	for(int i = 0; i < cardcount; i++){							// Loop to display the cards in players hand.
		player[i].display();
}
		
	cout << "\nPlease choose a card 1 through " << cardcount <<" to play: ";	// Announcement to the player.
	cin >> playercard;															// Card the player chose.
	
		while(playercard > cardcount  || playercard <= 0){		// While loop to check user inputs
		cin.clear();											
		cout << "Please choose a card you have." << endl;		// Error message for user.
		cin >> playercard;										// Card re-chosen for player.
	}
	
	playercard -= 1;											// Makes it so the array slot is the correct card the player selected (since 0-9 is the array, 1-10 input needs a minus 1)
	cout << "You chose the: ";	 								// Announcement of what card player chose to player.
	player[playercard].display();								// Displays the user selected card to the player.
	cout << endl;	
	
	if(comp1[comp1card].getsuit() != comp2[comp2card].getsuit() && player[playercard].getsuit() != comp2[comp2card].getsuit()){	// If no suit is equal to comp2's played card.
			cout << "Computer 2 wins the trick!" << endl;		// Comp2 wins.
			swap(player[playercard], player[cardcount - 1]);	// Swaps player chosen card with last card for that round.
			swap(comp1[comp1card], comp1[cardcount - 1]);		// Swaps comp1 chosen card with last card for that round.
			swap(comp2[comp2card], comp2[cardcount - 1]);		// Swaps comp2 chosen card with last card for that round.
			cout << endl;
			system("Pause");									// Sends value to main to let it know comp2 won.			
			return 3;
	}
	if(comp2[comp2card].getsuit() == player[playercard].getsuit() && comp2[comp2card].getsuit() == comp1[comp1card].getsuit()){	// Checks if all the suits for the played cards match.
		if(comp2[comp2card].getnum() > player[playercard].getnum() && comp2[comp2card].getnum() > comp1[comp1card].getnum()){	// Checks if comp2's card is the greatest.
			cout << "Computer 2 wins the trick!" << endl;		// Comp2 wins.
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);
			cout << endl;
			system("Pause");						
			return 3;
		}
	}
	if(comp1[comp1card].getsuit() != comp2[comp2card].getsuit()){			// Checks if comp1 suit is not equal to comp2's
		if(player[playercard].getsuit() == comp2[comp2card].getsuit()){		// Checks if players suit is equal to comp2's.
			if(player[playercard].getnum() > comp2[comp2card].getnum()){	// Checks if players card is higher than comp2's.
				cout << "Player wins the trick!" << endl;					// Player wins.
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 1;
			}
		}
	else{																	// Comp2 wins if the card doesn't match or isn't higher than player.
		cout << "Computer 2 wins the trick!" << endl;
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 3;		
	}
}
	if(player[playercard].getsuit() != comp2[comp2card].getsuit()){			// Checks if player suit is not equal to comp2's.
		if(comp1[comp1card].getsuit() == comp2[comp2card].getsuit()){		// Checks if comp1 suit is equal to comp2's
			if(comp1[comp1card].getnum() > comp2[comp2card].getnum()){		// Checks if comp2 card is higher than comp2's.
				cout << "Computer 1 wins the trick!" << endl;				// Comp1 wins.
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 2;
			}
		}
	else{																	// Comp2 wins if the card doesn't match or isn't higher than comp1.
		cout << "Computer 2 wins the trick!" << endl;
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 3;			
		}		
	}
	if(player[playercard].getsuit() != comp1[comp1card].getsuit()){			// Checks if player suit is not equal to comp2's.
		if(comp2[comp2card].getsuit() == comp1[comp1card].getsuit()){		// Checks if comp2 suit is equal to comp1's.
			if(comp2[comp2card].getnum() > comp1[comp1card].getnum()){		// Checks if comp2 card is higher than comp1's.
				cout << "Computer 2 wins the trick!" << endl;				// Comp2 wins.
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 3;
			}
		}
	else{																	// Comp1 wins if the card doesn't match or isn't higher than comp1's.
		cout << "Computer 1 wins the trick!" << endl;
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 2;			
		}		
	}
	if(player[playercard].getsuit() == comp1[comp1card].getsuit() && player[playercard].getsuit() == comp2[comp2card].getsuit()){	// Checks if player's suit is the same as comp1 and comp2.
		if(player[playercard].getnum() > comp1[comp1card].getnum() && player[playercard].getnum() > comp2[comp2card].getnum()){		// Checks if player's card is the same as comp1 and comp2.
			cout << "Player wins the trick!" << endl;\
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);			
			return 1;
			cout << endl;
		}
	}
	if(comp1[comp1card].getsuit() == player[playercard].getsuit() && comp1[comp1card].getsuit() == comp2[comp2card].getsuit()){		// Checks if comp1's suit is the same as player and comp2.
		if(comp1[comp1card].getnum() > player[playercard].getnum() && comp1[comp1card].getnum() > comp2[comp2card].getnum()){		// Checks if comp1's card is higher than player and comp2.
			cout << "Computer 1 wins the trick!" << endl;
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);			
			return 2;
			cout << endl;
		}
	}
}

int compfollow(Card player[],Card comp1[], Card comp2[], int cardcount){
	
	int playercard = 0, comp1card = 0, comp2card = 0; 	// Player and computers cards played in trick.
	int comp1red = 0, comp1white = 0, comp1blue = 0;	// Count for each suit the comp1 has in hand.
	int comp2red = 0, comp2white = 0, comp2blue = 0; 	// Count for each suit the comp2 has in hand.
	int comp1high = 0, comp2high = 0;					// Computer 1 and 2's highest numbered card in deck.
	int comp1low = 0, comp2low = 0;						// Computer 1 and 2's lowest numbered card in deck.	
//-----------------------------------------------------------------PLAYERS's TURN--------------------------------------------------------------------------------------------------//	
	for(int i = 0; i < cardcount; i++){							// Loop to get the cards for each hand.
		player[i].display();
}	
	
	cout << "\nPlease choose a card 1 through " << cardcount <<" to play: ";	// Announcement to the player.
	cin >> playercard;														// Card the player chose.
	
		while(playercard > cardcount  || playercard <= 0){		// While loop to check user inputs
		cin.clear();											
		cout << "Please choose a card you have." << endl;		// Error message for user.
		cin >> playercard;
	}
		
	playercard -= 1;											// Makes it so the array slot is the correct card the player selected (since 0-9 is the array, 1-10 input needs a minus 1)
	cout << "You chose the: ";	 								// Announcement to the player.
	player[playercard].display();								// Displays the user selected card to the player.
	cout << endl;
	
	for(int i = 0; i < cardcount; i++){																// Loop to check how many cards of each suit within computer 1's hand.
		if(comp1[i].getsuit() == "red"){
			comp1red += 1;																			// Comp1's number of red cards.
		}
		if(comp1[i].getsuit() == "white"){
			comp1white += 1;																		// Comp1's number of white cards
		}
		if(comp1[i].getsuit() == "blue"){
			comp1blue += 1;																			// Comp1's number of blue cards.
		}
	}
	// cout << comp1red << " red\n"<< comp1white << " white\n" << comp1blue << " blue" << endl;		// --TEST-- Check to see if the correct values are displayed.
	
	for(int i = 0; i < cardcount; i++){																// Loop to check how many cards of each suit within computer 2's hand.
		if(comp2[i].getsuit() == "red"){
			comp2red += 1;																			// Comp2's number of red cards.
		}
		if(comp2[i].getsuit() == "white"){
			comp2white += 1;																		// Comp2's number of white cards.
		}
		if(comp2[i].getsuit() == "blue"){
			comp2blue += 1;																			// Comp2's number of blue cards.
		}
	}
	// cout << comp2red << " red\n"<< comp2white << " white\n" << comp2blue << " blue" << endl;		// --TEST-- Check to see if the correct values are displayed.
//-----------------------------------------------------------------COMP1's TURN--------------------------------------------------------------------------------------------------//	
	if(player[playercard].getsuit() == "red"){														// Test statement for if the player chooses a red card. 
		if(comp1red < 1){																			// Checks to see if comp1 has and cards of red suit. 
			if(comp1blue > comp1white){																// If it doesn't have a red it chooses which suit has more cards. 
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "blue"){				// Tests to see if comp1's hand has a lowest value of suit blue.
						comp1low = comp1[i].getnum();
						comp1card = i;																// This sends the slot of card choosen to play.
					}
				}
			}
			else																					// If blue is NOT greater than white.
				for(int i = 0; i < cardcount; i++){													
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "white"){				// Check if the suit matches white and what the lowest card value for that suit. 
						comp1low = comp1[i].getnum();							
						comp1card = i;																// This sends the slot of card choosen to play.
					}
				}
			}
		else																						// Comp1 has a red suit card. 
			for(int i = 0; i < cardcount; i++){
				if(comp1[i].getnum() > player[playercard].getnum() && comp1[i].getsuit() == "red"){	// Check if the suit matches red and what the highest card value for that suit.
					comp1high = comp1[i].getnum();
					comp1card = i;																	// This sends the slot of card choosen to play.
		}
					if(comp1high == 0){																// If their isn't a card higher than the highest possible card.
						comp1low = player[playercard].getnum();										// Sets the players card to this lowest var.
						for(int i = 0; i < cardcount; i++){
							if(comp1[i].getnum() < player[playercard].getnum() && comp1[i].getnum() < comp1low && comp1[i].getsuit() == "red"){	// Check if the suit matches red and what the lowest card value for that suit and verses what is low in hand.
								comp1low = comp1[i].getnum();
								comp1card = i;														// This sends the slot of card choosen to play.
				}
			}
		}
	}
}
	comp1high = 0;																					// Resets variable to zero.
	comp1low = 0;																					// Resets variable to zero.
	if(player[playercard].getsuit() == "blue"){														// Checks if the player card is blue.
		if(comp1blue < 1){																			// Checks if comp1 has a blue.
			if(comp1red > comp1white){																// Checks if comp1 has more red than white.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "red"){				// Gets the lowest red card.  
						comp1low = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
			else																					// Has more white cards than red.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "white"){				// Gets the lowest white card.
						comp1low = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
		else																						// Comp1 has a blue card.
			for(int i = 0; i < cardcount; i++){
				if(comp1[i].getnum() > player[playercard].getnum() && comp1[i].getsuit() == "blue"){	// Gets the highest blue card.
					comp1high = comp1[i].getnum();
					comp1card = i;
			}
					if(comp1high == 0){																// If comp1 doesn't have a higher card than player.
						comp1low = player[playercard].getnum();										// Sets the players card to a low variable. 
						for(int i = 0; i < cardcount; i++){
							if(comp1[i].getnum() < player[playercard].getnum() && comp1[i].getnum() < comp1low && comp1[i].getsuit() == "blue"){	// Gets the lowest blue card.
								comp1low = comp1[i].getnum();
								comp1card = i;
				}
			}
		}
	}
}
	comp1high = 0;
	comp1low = 0;
	if(player[playercard].getsuit() == "white"){											// Checks if the player card is white.
		if(comp1white < 1){																	// Checks if comp1 has a white card.
			if(comp1red > comp1blue){														// Checks if there is more red than blue card.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "red"){		// Gets the lowest red card.
						comp1low = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
			else																			// If there are more blue than red cards.
				for(int i = 0; i < cardcount; i++){
					if(comp1[i].getnum() < comp1low && comp1[i].getsuit() == "blue"){		// Gets the lowest blue card.
						comp1low = comp1[i].getnum();
						comp1card = i;
					}
				}
			}
		else																				// Comp1 has a white card.
			for(int i = 0; i < cardcount; i++){
				if(comp1[i].getnum() > player[playercard].getnum() && comp1[i].getsuit() == "white"){	// Gets the greates white card.
					comp1high = comp1[i].getnum();
					comp1card = i;
		}
				if(comp1high == 0){															// If comp1 doesn't have a greater card than player.
					comp1low = player[playercard].getnum();									// Set player card to a low variable.
					for(int i = 0; i < cardcount; i++){
						if(comp1[i].getnum() < player[playercard].getnum() && comp1[i].getnum() < comp1low && comp1[i].getsuit() == "white"){	// Gets the lowest white card.
							comp1low = comp1[i].getnum();
							comp1card = i;
				}
			}
		}
	}
}

	
	cout << "Computer 1 plays the";		// Announcement to the player.
	comp1[comp1card].display();			// Comp1's played card.
	cout << endl;
//-----------------------------------------------------------------COMP1's TURN--------------------------------------------------------------------------------------------------//	
	if(player[playercard].getsuit() == "red"){												// Checks if players card is suit red.
		if(comp2red < 1){																	// Checks if comp2 has a red suit.
			if(comp2blue > comp2white){														// Checks if there are more blue than white.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "blue"){		// Gets the lowest blue card.
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
			else																			// Comp2 has more white than blue cards.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "white"){		// Gets the lowest white card.
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
		else																				// Comp2 has a red card.
			for(int i = 0; i < cardcount; i++){
				if(comp2[i].getnum() > player[playercard].getnum() && comp2[i].getsuit() == "red"){	// Comp2 plays highest red card. 
					comp2high = comp2[i].getnum();
					comp2card = i;
		}
					if(comp2high == 0){																// If comp2 doesn't have a higher card than player.
						comp2low = player[playercard].getnum();										// Sets players card to a low variable. 
						for(int i = 0; i < cardcount; i++){
							if(comp2[i].getnum() < player[playercard].getnum() && comp2[i].getnum() < comp2low && comp2[i].getsuit() == "red"){	// Gets the lowest red card. 
								comp2low = comp2[i].getnum();
								comp2card = i;
				}
			}
		}
	}
}
	comp2high = 0;	// Reset variable.
	comp2low = 0;	// Reset variable. 
	if(player[playercard].getsuit() == "blue"){															// Checks if the players suit is blue. 
		if(comp2blue < 1){																				// Checks if comp2 has a blue.
			if(comp2red > comp2white){																	// Checks if comp2 has more red than white. 
				for(int i = 0; i < cardcount; i++){	
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "red"){					// Gets the lowest red card. 
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
			else																						// Comp2 has more white than red cards. 
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "white"){					// Gets the lowest white card. 
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
		else																							// Comp2 has a blue card. 
			for(int i = 0; i < cardcount; i++){
				if(comp2[i].getnum() > player[playercard].getnum() && comp2[i].getsuit() == "blue"){	// Gets the highest blue card. 
					comp2high = comp2[i].getnum();
					comp2card = i;
			}
					if(comp2high == 0){																	// If the comp2 doesn't have a card greater than the player. 
						comp2low = player[playercard].getnum();											// Sets the players card to the lowest variable. 
						for(int i = 0; i < cardcount; i++){
							if(comp2[i].getnum() < player[playercard].getnum() && comp2[i].getnum() < comp2low && comp2[i].getsuit() == "blue"){	// Gets the lowest blue.
								comp2low = comp2[i].getnum();
								comp2card = i;
				}
			}
		}
	}
}
	comp2high = 0;	// Reset variable. 
	comp2low = 0;	// Reset variable. 
	if(player[playercard].getsuit() == "white"){										// Checks to see if players suit is white. 
		if(comp2white < 1){																// Check if comp2 has a white. 
			if(comp2red > comp2blue){													// Check if comp2 has more red than blue. 
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "red"){	// Gets the lowest red card. 
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
			else																		// If there are more blue than white.
				for(int i = 0; i < cardcount; i++){
					if(comp2[i].getnum() < comp2low && comp2[i].getsuit() == "blue"){	// Gets the lowest blue card. 
						comp2low = comp2[i].getnum();
						comp2card = i;
					}
				}
			}
		else																			// Comp2 has a white card. 
			for(int i = 0; i < cardcount; i++){
				if(comp2[i].getnum() > player[playercard].getnum() && comp2[i].getsuit() == "white"){	// Gets the highest white card. 
					comp2high = comp2[i].getnum();
					comp2card = i;
		}
				if(comp2high == 0){																		// If comp2 doesn't have a higher card than player. 
					comp2low = player[playercard].getnum();												// Sets the player card to a low variable. 
					for(int i = 0; i < cardcount; i++){
						if(comp2[i].getnum() < player[playercard].getnum() && comp2[i].getnum() < comp2low && comp2[i].getsuit() == "white"){	// Gets the lowest white card. 
							comp2low = comp2[i].getnum();
							comp2card = i;
				}
			}
		}
	}
}

	cout << "Computer 2 plays the";		// Announcement to the player.
	comp2[comp2card].display();			// Comp2's selected card. 
	cout << "\n" << endl;
	
	if(comp1[comp1card].getsuit() != player[playercard].getsuit() && comp2[comp2card].getsuit() != player[playercard].getsuit()){	// Check to see if comp1 and comp2 card is not equal to the player. 
			cout << "Player wins the trick!" << endl;			// Player wins. 
			swap(player[playercard], player[cardcount - 1]);	// Swap the players card with the last card in hand. 
			swap(comp1[comp1card], comp1[cardcount - 1]);		// Swap the comp1 card with the last card in hand.
			swap(comp2[comp2card], comp2[cardcount - 1]);		// Swap the comp2 card with the last card in hand.
			cout << endl;
			system("Pause");									
			return 1;											// Returns 1 to be used in main. 
	}
	if(player[playercard].getsuit() == comp1[comp1card].getsuit() && player[playercard].getsuit() == comp2[comp2card].getsuit()){	// Checks if the player cards suit is equal to the comp1 and comp2. 
		if(player[playercard].getnum() > comp1[comp1card].getnum() && player[playercard].getnum() > comp2[comp2card].getnum()){		// Checks if the player card is greater than comp1 and comp2. 
			cout << "Player wins the trick!" << endl;			// Player wins. 
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);
			cout << endl;
			system("Pause");						
			return 1;
		}
	}
	if(comp2[comp2card].getsuit() != player[playercard].getsuit()){				// Checks if comp2 suit is equal to players card. 
		if(comp1[comp1card].getsuit() == player[playercard].getsuit()){			// Checks if comp1 suit is equal to the players card.
			if(comp1[comp1card].getnum() > player[playercard].getnum()){		// Checks if comp1 card is greater than the players card. 
				cout << "Computer 1 wins the trick!" << endl;					// Comp1 wins. 
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 2;
			}
		}
	else{																		// If comp1's suit isn't equal to player.
		cout << "Player wins the trick!" << endl;								// Player wins. 
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 1;		
	}
}
	if(comp1[comp1card].getsuit() != player[playercard].getsuit()){				// If comp1's suit isn't equal to player.
		if(comp2[comp2card].getsuit() == player[playercard].getsuit()){			// If comp2 is equal to player.
			if(comp2[comp2card].getnum() > player[playercard].getnum()){		// Checks if comp2 is greater than player. 
				cout << "Computer 2 wins the trick!" << endl;					// Comp2 wins.
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 3;
			}
		}
	else{																		// If comp2 suit isn't equal to player. 
		cout << "Player wins the trick!" << endl;								// Player wins. 
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 1;			
		}	
	}
	if(comp2[comp2card].getsuit() != player[playercard].getsuit()){				// If comp2 suit doesn't equal player suit. 
		if(comp1[comp1card].getsuit() == player[playercard].getsuit()){			// Checks if comp1 suit is equal to player suit. 
			if(comp1[comp1card].getnum() > player[playercard].getnum()){		// Checks if comp1 card is greater than player card. 
				cout << "Computer 1 wins the trick!" << endl;					// Comp1 wins. 
				swap(player[playercard], player[cardcount - 1]);
				swap(comp1[comp1card], comp1[cardcount - 1]);
				swap(comp2[comp2card], comp2[cardcount - 1]);
				cout << endl;
				system("Pause");						
				return 2;
			}
		}	
	else{																		// If comp1 suit doesn't equal player. 
		cout << "Player wins the trick!" << endl;								// Player wins. 
		swap(player[playercard], player[cardcount - 1]);
		swap(comp1[comp1card], comp1[cardcount - 1]);
		swap(comp2[comp2card], comp2[cardcount - 1]);
		cout << endl;
		system("Pause");						
		return 1;			
		}	
	}	
	if(comp1[comp1card].getsuit() == player[playercard].getsuit() && comp1[comp1card].getsuit() == comp2[comp2card].getsuit()){	// Check if comp1 suit is equal to comp2 and player.
		if(comp1[comp1card].getnum() > player[playercard].getnum() && comp1[comp1card].getnum() > comp2[comp2card].getnum()){	// Check if comp1 card is greater than comp2 and player card. 
			cout << "Computer 1 wins the trick!" << endl;																		// Comp1 wins. 
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);			
			return 2;
			cout << endl;
		}
	}
	if(comp2[comp2card].getsuit() == player[playercard].getsuit() && comp2[comp2card].getsuit() == comp1[comp1card].getsuit()){	// Check if comp2 suit is equal to comp1 and player.
		if(comp2[comp2card].getnum() > player[playercard].getnum() && comp2[comp2card].getnum() > comp1[comp1card].getnum()){	// Check if comp2 card is greater than comp1 and player card.
			cout << "Computer 2 wins the trick!" << endl;																		// Comp2 wins. 
			swap(player[playercard], player[cardcount - 1]);
			swap(comp1[comp1card], comp1[cardcount - 1]);
			swap(comp2[comp2card], comp2[cardcount - 1]);
			return 3;
			cout << endl;
		}
	}
}

