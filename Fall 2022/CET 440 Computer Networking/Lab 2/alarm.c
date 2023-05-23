/*
 *  alarm.c - demo program to show use of Unix signal(2) and alarm(2) 
 *	      system calls
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

main()
{
    void timeout();		// declare timeout() as a void function
    int slept = 0;		// counter for numbers of times sleep called

    signal( SIGALRM, timeout );	// where to go when ALARM signal received
    alarm( 5 );			// how many seconds till ALARM signal

    // an infinite loop
    while( 1 )
    {
	sleep( 2 );
	printf( "main(): I slept %i times\n", ++slept );
    }
    return( 0 );		// will never get here anyway...
}


// asynchronously called function to handle programmed timeout alarm
// signo - the signal number, passed by kernel 

void timeout( int signo )
{
    alrm_cnt++;			// bump global counter
    printf( "\n*** received alarm %i (signal #%i) ***\n\n", alrm_cnt, signo );
    /* reset things for next time interval */
    if ( signal( SIGALRM, timeout ) == SIG_ERR )
	perror( "signal error in timeout()" );
    alarm( 6 );
}
