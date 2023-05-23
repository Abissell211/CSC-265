#include <stdlib.h>
#include <stdio.h>

void funval(int first, int second){
	first += first;
	second += second;
}

void funref(int *first, int *second){
	*first += *first;
	*second += *second;
}

int main(){
	int list[2] = {1, 3};
	
	printf("list[0] = %d	list[1] = %d\n", list[0], list[1]);
	funval(list[0], list[1]);
	printf("list[0] = %d	list[1] = %d\n", list[0], list[1]);
	
	list[0] = 1;
	list[1] = 3;
	
	printf("list[0] = %d	list[1] = %d\n", list[0], list[1]);
	funref(&list[0], &list[1]);
	printf("list[0] = %d	list[1] = %d\n", list[0], list[1]);
	
	return(0);
}
