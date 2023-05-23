/*
 *  Client: Data Share Program
 *
 *  	10-Oct-22 : 
 *		Andrew Bissell
 *		Joshua Hughes
 *		Noah Proctor
 *
 *		Contains the main function and includes the lab4.h file and the functions prototypes present
 *			in the lab4.h, full functions are found in the FuncsLab4.c
 */

#include <stdio.h>			// for standard system I/O stuff
#include <errno.h>			// for error handling on system calls
#include <sys/types.h>		// for system defined types
#include <sys/ipc.h>		// for IPC permission structure
#include <sys/shm.h>		// for shared memory facility defines
#include <stdlib.h>
#include <time.h>
#include "Lab4.h"

#define SHMKEY 0x774000 + 01	// Server shared memory key


int main (){
    int shm_id, i, n;		
	struct student *z;// z will point to shared memory array

//  --------------------------------------------------------------------
//  call system library function to get pre-existing shared memory
//  --------------------------------------------------------------------
    shm_id = shmget( SHMKEY, 0, 0 );

    if ( shm_id == -1 )		// check shmget() return value
    {
	printf( "\nError: shmget() failed, errno = %i\n", errno );
	perror( "shmget()" );
	exit( -1 );
    }
    else
	printf( "\nshmget() successful, shm_id = %i\n", shm_id );

//  --------------------------------------------------------------------
//  attach variable z to shared memory segment
//  --------------------------------------------------------------------
    z = (struct students*) shmat( shm_id, 0, SHM_RDONLY );
    if ( (int) z == -1 )
    {
	printf( "Error: shmat() failed, errno = %i\n", errno );
	perror( "shmat()" );
	exit( -1 );
    }
    
//  access data from shared memory region
    //Show_Struct_Info(z);
    Students_Averages(z);	
    putchar( '\n' );


//  --------------------------------------------------------------------
//  done with shared memory, detach from it
//  --------------------------------------------------------------------
    shmdt( (void *) z );

    return( 0 );
}
