/* qt.c - Displays time in real English, also chimes.      		*/
/* 	Mark Dapoz, Converted to C for UNIX, April 1986 		*/
/*	Mike Cowlishaw,  December 1979 - December 1982   		*/
/*	   86/11/13 - major update, code really cleaned up :-)		*/

#include <sys/types.h>
#include <time.h>
#define	 TIMESIZ	80	/* size of our saying			*/

#define	 DEBUG
#undef	 DEBUG

char *h[13] = {			/* numbers in words			*/
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",  
	"seven", 
	"eight",
	"nine",
	"ten",  
	"eleven", 
	""
};

main(argc,argv)
int argc;
char **argv;

{
	char	  ot[TIMESIZ];		/* words to display		*/
	short int hr,mn,sc;			/* time of day			*/
	short int five_mn;			/* time to nearest five min	*/
	time_t	  clock;			/* struct for time function	*/
	struct tm *tm;
	struct tm *localtime();		/* conver to local time function*/
	time_t	  time();			/* GMT time function		*/

	strcpy(ot,"It's ");			/* our saying			*/

	time(&clock);				/* GMT time of day from system	*/
	tm=localtime(&clock);		/* get local time 		*/
	hr=(short int)tm->tm_hour;
	mn=(short int)tm->tm_min;
	sc=(short int)tm->tm_sec;

#ifdef DEBUG
	if (argc > 1) {				/* debug			*/
		hr=atoi(argv[1]);
		mn=atoi(argv[2]);
		sc=atoi(argv[3]);
		printf("hr=%u, mn=%u, sc=%u\n",hr,mn,sc);
	}
#endif
     
	if (sc > 29) 				/* round up mins 		*/
		mn+=1;
	if (mn > 32)				/* round up hours		*/
		hr+=1;
								/* how far off 5 min mark?	*/
	switch(mn%5) {	
		case 0: 				/* exact hour			*/
			break;
 		case 1:	
			strcat(ot,"just past ");
			break;
		case 2:
			strcat(ot,"just after ");
			break;
		case 3:
			strcat(ot,"nearly ");
			break;
		case 4:
			strcat(ot,"almost ");
			break;
	}
	five_mn = mn;
	if (mn%5 >= 3)			/* round up			*/
		five_mn = mn+5;
    					/* what part of the hour?	*/ 
	switch(five_mn-(five_mn%5)) {	/* 5 minute resolution		*/
	case 0:
	case 60:	
		break;
	case 5:
		strcat(ot,"five past ");
		break;
	case 10:	
		strcat(ot,"ten past ");
		break;
	case 15:
		strcat(ot,"a quarter past ");
		break;
	case 20:	
		strcat(ot,"twenty past ");
		break;	
	case 25:
		strcat(ot,"twenty-five past ");
		break;
	case 30:
		strcat(ot,"half past ");
		break;
	case 35:
		strcat(ot,"twenty-five to ");
		break;
	case 40:
		strcat(ot,"twenty to ");
		break;
	case 45:
		strcat(ot,"a quarter to ");
		break;
	case 50:
		strcat(ot,"ten to ");
		break;
	case 55:
		strcat(ot,"five to ");
		break;
	}

	if ((hr%12) == 0)
		midnoon(&hr,ot);		/* noon and midnight		*/
	if (hr > 12)
		hr -= 12;				/* get rid of 24-hour clock 	*/
	else
		if (hr == 0)
			hr=12;				/* cater for midnight		*/
								/* add the o'clock		*/
	strcat(ot,h[hr-1]);
	if ((mn%60 == 0) && (hr != 12))
		strcat(ot," o'clock");
	strcat(ot,".");				/* end of sentence		*/
	if ((mn%15) == 0) 			/* chime every 15 minutes	*/
		chime(&hr,&mn);
	printf("\n%s\n\n",ot); 		/* town crier :-)		*/
}

midnoon(hr,ot)					/* is it noon or midnight?	*/
short int *hr;					/* hour of day		*/
char *ot;						/* the saying		*/

{
	if (*hr == 12) 				/* it's noon			*/
		strcat(ot,"Noon");
	else 						/* it's midnight		*/
		strcat(ot,"Midnight");
	*hr=12;						/* make it noon			*/
}
     
chime(hr,mn)					/* ring the bells		*/
short int *hr;					/* hour of day		*/
short int *mn;					/* minute of day	*/

{
	int	num,i;
	char	bell[16], ring[80];

	if ((*mn%60) == 0) {		/* on the hour?			*/
		strcpy(bell,"Bong");
		num = *hr;
	}
	else {	        			/* must be quarter hour		*/
		strcpy(bell,"Ding-Dong");
		num=(*mn%15);
	}
	strcpy(ring,"(");
	strcat(ring,bell);			/* ring the bells		*/
	for (i=0;i < num-1;i++) {
		strcat(ring,",");
		strcat(ring,bell);
	}
	strcat(ring,"!)");
	printf("\n%s",ring);
}
