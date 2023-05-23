// ***** 0. Documentation Section *****
// main.c
//     Runs on TM4C123
//     UART runs at 115,200 baud rate 
//     Daniel Valvano
//     June 17, 2013
// Lab 5
//      Jon Valvano and Ramesh Yerraballi
//      January 15, 2016

// ***** 1. Pre-processor Directives Section *****
#include <stdio.h>   // standard C library 
#include "uart.h"    // functions to implment input/output
#include "TExaS.h"   // Lab grader functions

// ***** 2. Global Declarations Section *****

// FUNCTION PROTOTYPES: Each subroutine defined
unsigned long Calc_Area(unsigned long l, unsigned long w); 
void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****
int main (void) {
  unsigned long length, width, area;
  TExaS_Init(UART_PIN_PA0,UART_PIN_PA1); // this initializes the TExaS grader lab 5
  UART_Init();    // initialize UART for printing
  printf("\nThis program calculates areas of rectangular rooms.\n");
  EnableInterrupts();  // the grader needs interrupts
  while(1) {
    printf("\nGive length: "); scanf("%ld", &length);  // Get input
    printf("\nGive width: ");  scanf("%ld", &width);   // Get input
    area = Calc_Area(length, width);
    printf("\nArea of the room = %ld\n",  area);
  }
}

// Computes the Area of a rectangular room whose sides are given
// Input:  the length (l) and width (w) are the dimensions of a rectangle
// Output: the area of the rectangular room 
// Notes:  Return a result of zero if 
//    the length is less than 3,  
//    the width is less than 3,  
//    the length is greater than 20 or  
//    the width is greater than 20. 
unsigned long Calc_Area(unsigned long l, unsigned long w) {	// (returns unsigned long) Calc_Area(recieves data unsigned long l, w)
  unsigned long result;
  if((l >= 3 && l <= 20) && (w >= 3 && w <= 20)){		// Checks if the range for length and width is [3,20]
		result = l*w;																		// If it is true, the result is the length times the width	
		return(result);																	// Return the result to the function call
	}
	else																							// If it is false,
	{
		printf("\nERROR not within range! [3,20]");				// Error message
		return(0);																			// Return zero to the function call
	}
}