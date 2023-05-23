/*
 *  sumation.c - example C program to calculate sumation of given number
 *
 *  Getting sumation using a for loop:
 *  	19-Sep-94 : Prof. Jeffrey Sumey
 *
 *	Getting sumation using recursive function:
 *  	25-Aug-22 : Andrew D. Bissell
 *
 *	scan() function use:
 *		01-Sep-22 : Scott A. Trunzo
 *
 *  NOTES: - For normal operation remove the while loop from the main(), it not take negative numbers
 *			 and will force cast decimal numbers to int only keeping what is left of the decimal point.
 		   - If the while loop is present, any correct data that is passed to the program (positive whole
 		     number) it will run correctly.
 		   - If the while loop is present, and a decimal number is given the program will keep forceing
 		     through all of the printf's and scanf's until it crashes. The forced cast to int works but
 		     for some reason the while loop does not like any number that was once a decimal.
 		   - The recursive function works properly but cannot compute a large value due to its recursive
 		     function calling. It causes the program to time out after a period or give incorrect values.
 		   - The for loop for summation works better since it requires less time and function calls to get
 		     the answer for a given value. Since this is the case the max number given to the for loop is 
 		     much greater than the recursive function.
 		   - For recursive function: At about 261500 - 262000 causes the program to crash
 		   - For the for loop summation: At 92681 causes the program to return last correct summation
 */

#include <stdio.h>


main()
{
  int i = 0, number = 1, sum = 0;

	while(number != 0){						// Loop to allow multiple inputs before quitting
	//fflush(stdin);
	scan();
	// Intro and information to user that collects a number
		printf( "Sumation Calculator\n" );
		printf( "Enter 0 to quit \n");
	  	printf( "Enter number: " );
	  	scanf( " %i", &number );
	  	
	  	if(number < 0){
	  		printf("ERROR: Incorrect data\n");
			printf( "Sumation Calculator\n" );
			printf( "Enter 0 to quit \n");
		  	printf( "Enter number: " );
		  	scanf( " %i", &number );	
		}
		
	
	// Original code used to check the recursive code
		for (i=0; i<=number; i++)
		  	sum=sum+i;
		  	
		printf( "The Original  Sumation of %i is %ld.\n", number, sum);
		sum = 0;
		
	// Recursive sumation
	  	printf( "The Recursive Sumation of %i is %ld.\n\n\n", number, Recursive(number, sum));
	  	
	  	if(number != 0)
			number = 1;
	}
	
	
	printf("GOODBYE!");
 	return 0;
}

// Takes the user input number to add to the sum recursivly
int Recursive(int number, int sum){
// check to see if we are done adding the number
	if(number > 0){
	// if not done adding, add current number to sum
		sum += number;
		
		//printf("Number = %d \n", number);	// TESTING
		//printf("Sum    = %d \n", sum);	// TESTING
		
	// then call the function again with the current number subtracted by 1
		Recursive(number - 1, sum);
	}
	else
	// else we are done return the sum to the print statement
		return sum;
}

int scan(void)
{
	// assigns the temporary value, temp.
	int temp;

	// scans for temp.
	scanf("%d",&temp);
		
	// the following snippet is sourced from https://www.geeksforgeeks.org/clearing-the-input-buffer-in-cc/
	// acts like fflush, without using fflush. Prevents infinite loops due to lingering input.
	while ((getchar()) != '\n');

	// returns temp, ending the function.
	return temp;
};

