#include <stdio.h>
#include <stdlib.h>

int main(){
	
	int a = 10, b = 0, c = 5, i = 10;
	
	// Function taken from chapter 7 lesson
	if((a > b) || ((b++) / 3))
		printf("b is %d\n", b);
	
	// My function to test short-circuit 
	b = 50;
	if(b || ++b)
		printf("b is %d\n", b);
		
	
	return(0);
}
