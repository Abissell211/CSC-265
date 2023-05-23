#include <stdio.h>
#include <stdlib.h>

int fun(int* a){
	*a += 10;
	return 5;
}

int main(){
	
	int a, b;
	
	a = 10;
	b = a + fun(&a);
	printf("With the function call on the right, ");
	printf(" b is: %d\n", b);
	printf(" a is: %d\n", a);
	
	a = 10;
	b = fun(&a) + a;
	printf("With the function call on the left, ");
	printf(" b is: %d\n", b);
	printf(" a is: %d\n", a);
	
	return(0);
}


