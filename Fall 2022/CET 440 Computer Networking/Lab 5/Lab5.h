/*
 *  Client: Lab 5 Socket Program
 *
 *  	10-Nov-22 : 
 *		Andrew Bissell
 *		Joshua Hughes
 *		Noah Proctor
 *
 *		Contains the all the prototypes for
 *			the functions found in FuncsLab5.c
 */
 
#ifndef Lab5
#define Lab5

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <time.h>

#define RCVBUFSIZE 1024   /* Size of receive buffer */
#define SNDBUFSIZE 1024   /* Size of receive buffer */

char *strupr(char * text);
void UpdateFile(char RName[], char LTime[], FILE *log);

#endif
