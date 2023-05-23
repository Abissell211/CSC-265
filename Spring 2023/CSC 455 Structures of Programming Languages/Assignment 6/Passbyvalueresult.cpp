#include <stdio.h>

int a=1;
int b=3;

void fun(int x, int y) {
	a += x;
	b += y;
}

int main() {
    fun(a,b);
    printf("a %d b %d\n",a,b);
    return(0);
}
