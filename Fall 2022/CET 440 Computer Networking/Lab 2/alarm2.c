/*
 *  alarm2.c - demo program to show use of Unix signal(2) and alarm(2) 
 *	       system calls
 *  17-Oct-94 :jss
 *
 *  important things to look at for this program:
 *	include files: <signal.h> or <sys/signal.h>
 *	man pages: signal(3HEAD), signal(3C), alarm(2)
 */

#include <stdio.h>		// for standard system I/O stuff
#include <errno.h>		// for error handling on system calls
#include <signal.h>		// for signal handling

int alrm_cnt = 0;		// number of times alarm() used

void timeout();			// declare timeout() as a void function
void cancel();			// routine to handle interrupt signal
main()
{
    signal( SIGINT, cancel );	// catch process INTerrupt signals
    /* an infinite loop */
    while( 1 )
    {
	signal(_SIGALRM, timeout );
	alarm( 1 );		// set alarm timer for 3 seconds
	pause();		// suspend process 'till signal
	printf( "main(): I paused %i times\n", alrm_cnt );
    }
    return( 0 );		// will never get here anyway...
}
// asynchronously called function to handle programmed timeout alarm
void timeout( int signo )
{
    alrm_cnt++;			// bump global counter
    printf( "\n*** received alarm %i (signal #%i) ***\n", alrm_cnt, signo );
}


// asynchronously called function to handle process interrupt signal

void cancel( int signo )
{
    printf( "\n\n*** Interrupt signal (#%i) caught, exiting program ***\n",
	    signo );
    exit( -1 );			// what if we don't?
}
