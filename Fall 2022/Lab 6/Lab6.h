#ifndef Lab6
#define Lab6

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
#define CSIZE 95
#define ASCIIS 32
#define SSIZE 1024


void encrypt(int * key, char * ptext, char * ctext);
void decrypt(int * key, char * ptext, char * ctext);
char *strupr(char * text);
void UpdateFile(char RName[], char LTime[], FILE *log);
int passwordCheck(char * password);

#endif
