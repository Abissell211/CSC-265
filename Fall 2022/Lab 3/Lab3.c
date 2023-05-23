/*
 *  Encryption Program
 *
 *	Digital Clock Program:
 *  	22-Sep-22 : 
 *		Andrew Bissell
 *		Joshua Hughes
 *		Noah Proctor
 *	
 *	Acknowledgements: https://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Shuffle.h"

#define ASCII_START 32
#define ASCII_END 126
#define ASCII_COUNT 95
#define SIZE 50

int main(void){
    int i = 0;
    int j = 0;
    int random = 0;
    int test = 0;
    time_t t;
    char ASCII_CHAR[ASCII_COUNT];
    char CYPHER[ASCII_COUNT];
	char USER_IN[SIZE]={};
	char TEMP[2] = {13};
	size_t count = 0;
	int check = 0; 
	// initialize random seed
    srand((unsigned) time(&t));

	// Fill ASCII_CHAR with ASCII characters
    while (i < ASCII_COUNT){
        ASCII_CHAR[i] = i+ASCII_START;
        i++;
    }

	// Ensure that CYPHER is clear
	for (i=0;i<ASCII_COUNT;i++){
		CYPHER[i] = i+ASCII_START;
	}
	
	shuffle(CYPHER,95);
	printf("Please input a string, finished with an Enter: \n");
	// Take a user created string into the USER_IN char array
	// fgets obtains the input and places it in X, uses a size limit, and where
	// fgets(X, MAX_X_SIZE, stdin);
	fgets(USER_IN,SIZE,stdin);
	//printf(" \n %d \n  ",USER_IN[4]);
//scanf("%s", USER_IN);
	// Get the size of the string in the array (stops at first null char so and space ends the string)
		//scanf stops at first space, str stops at first null (and will include enter)
	count = strlen(USER_IN);
	// apply the cypher to the user input string
	i=0;								// reset i
	while(count != 0){					// keep altering string until the end of the string is reached
		//USER_IN[i] -= 32;				// lower the current letter to the correct CYPHER location
		USER_IN[i] = CYPHER[USER_IN[i]-32];// at the current location apply the CYPHER character
		count--;
		i++;
	}
	
	// Print the scrambled user input string
	printf("The encrypted string is "); 
	for (count=0;count<i;count++){
	printf("%c",USER_IN[count]);
	}
	printf("\n");


	printf("The encryption key (i.e., the substitution) is original[substitution] \n");


	// show key
	for (i=0;i<ASCII_COUNT;i++){
	
	printf(" %c ",CYPHER[i]); printf("[ %c ]",ASCII_CHAR[i]);
	if (i%10 ==1)
	printf("\n");
	}
	printf("\n");
	
			
		
return 0;
}
