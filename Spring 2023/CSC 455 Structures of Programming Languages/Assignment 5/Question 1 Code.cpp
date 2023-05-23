#include <stdlib.h>
#include <stdio.h>

void PbV(int a, int b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void PbR(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main(){
	int value = 2, list[5] = {1,3,5,7,9};
	PbV(value, list[0]);
	PbV(list[0], list[1]);
	PbV(value, list[value]);
	
	printf("value = %d\n\n", value);
	for(int i = 0; i < 5; i++)
		printf("list[%d] = %d\n", i, list[i]);
	
	printf("\n");
		
	PbR(&value, &list[0]);
	PbR(&list[0], &list[1]);
	PbR(&value, &list[value]);
	
	printf("value = %d\n\n", value);
	for(int i = 0; i < 5; i++)
		printf("list[%d] = %d\n", i, list[i]);
		
	return(0);
}
