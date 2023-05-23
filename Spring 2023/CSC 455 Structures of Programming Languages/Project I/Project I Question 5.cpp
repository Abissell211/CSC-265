#include <stdio.h>
int main(){
	int a = 1, b = 2, c = 3;
	int f = 0;
	
	while(f != 1){
		int b = 21, c = 22, d = 4;
		printf("#1  =  ");
		printf("%d, %d, %d, %d\n", a,b,c,d);
		// --- //	1 >>> local b, c, d
		f = 1;
		while(f != 0){
			int c = 23, d = 24, e = 5;
			printf("#2  =  ");
			printf("%d, %d, %d, %d, %d\n", a,b,c,d,e);
			// --- //	2
			f = 0;
		}
	f = 1;
	printf("#3  =  ");
	printf("%d, %d, %d, %d\n", a,b,c,d);
	// --- //	3
	}
printf("#4  =  ");
printf("%d, %d, %d\n", a,b,c);
// --- //	4
return 0;
}
