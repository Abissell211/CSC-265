/*
 *  Client: Lab 5 Socket Program
 *
 *  	10-Nov-22 : 
 *		Andrew Bissell
 *		Joshua Hughes
 *		Noah Proctor
 *
 *		Contains the functions used in the lab5.c
 */
 
#include "Lab5.h"

char *strupr(char * text)
{
	int i, j=strlen(text);
	
	for (i=0;i<j;i++)
	{
		if ((text[i]>=97)&&(text[i]<=122))
			text[i]=text[i]-32;
	}
	return text;
}

void UpdateFile(char RName[], char LTime[], FILE *log){
	fputs(RName, log);		// update time
	fputs(LTime, log);		// update register status
}
