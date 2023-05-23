#include "Lab6.h"

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
void permutation(int * key, int * pool, int length)
{
	int asize, num=length, i, j;
	
	for(asize=0; asize<length; asize++)
	{
		pool[asize]=asize;
	}
	
	for(asize=0; asize<length; asize++)
	{	
		i=rand() % num;
		key[asize]=pool[i];
//		printf("i=%d  key[%d]=%d \n",i,asize, key[asize]);
		for(j=i; j<length; j++)
		{
			pool[j]=pool[j+1];
		}
		num=num-1;
	}
}

void encrypt(int * key, char * ptext, char * ctext)
{
	int i, length;
	//int pool[CSIZE];
	//int key[CSIZE];

	
	//permutation(key, pool, CSIZE); //generate keys

	length=strlen(ptext);
	
	for (i=0; i<length; i++)
	{
		ctext[i]=key[ptext[i]-ASCIIS]+ASCIIS;  //The first keyboard printable character have an ASCII code 32, defined as ASCIIS.
	}
}
void decrypt(int * key, char * ctext, char * ptext)
{
	int i, length;
	int j;
	//int pool[CSIZE];
	//int key[CSIZE];

	
	//permutation(key, pool, CSIZE); //generate keys

	length=strlen(ptext);
	
	for (i=0; i<length; i++)
	{
		for (j=0; j<CSIZE;j++){
			if((ctext[i]-32) == key[j])
				{break;}
		}
		ptext[i]=j+32;
	}
}
int passwordCheck(char * password){
	int i=0;
	int length;
	length = strlen(password);
	int upperCount=0;
	int lowerCount=0;
	int specialCount=0;
	int numberCount=0;
	int totalSum=0;
	if (length< 8){
		return 0;
	}

	for (i=0; i<length; i++){
		if(48 <= password[i] && 57 >= password[i]){
			numberCount =1;
			continue;
		}
		if (97 <= password[i] && 122 >= password[i]){
			lowerCount=1;
			continue;
		}
		if (33 <= password[i] && 46 >= password[i]){
			specialCount=1;
			continue;
		}
		if(65 <= password[i] && 90 >= password[i]){
			upperCount=1;
			continue;
		}
	}
	totalSum = upperCount + lowerCount + specialCount + numberCount;
	if (totalSum >=3){
		return 1;}
	else {
		return 0;}
}

