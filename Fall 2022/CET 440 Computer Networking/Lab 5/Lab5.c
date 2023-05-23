/*
 *  Client: Lab 5 Socket Program
 *
 *  	10-Nov-22 : 
 *		Andrew Bissell
 *		Joshua Hughes
 *		Noah Proctor
 *
 * 		Contains the main function and includes the lab5.h file and the functions prototypes present
 *			in the lab5.h, full functions are found in the FuncsLab5.c
 */

#include "Lab5.h"

int main(int argc, char *argv[])
{
    int servSock = 0, n = 0;
    char recvBuff[RCVBUFSIZE];
    char sendBuff[SNDBUFSIZE];
    char command[20], username[8];
    struct sockaddr_in serv_addr; 
    int quit=0, mistake=0, bytesRcvd;
    char servIP[16];
    int port;
    int i=0;
    int count = 0;
    
    // File
    FILE *log;
    // Registration Status String
    char RName[10];
    char *r = RName;
    size_t RegName = 10;
    // Last Login Time String
    char LTime[50];
    char *l = LTime;
    size_t LoginTime = 50;
    
    ssize_t RLine;
    ssize_t LogLine;
    
    time_t l_time;
    struct tm *c_time;
    time(&l_time);
    c_time = localtime(&l_time);
	
//---------------------------------------------------Connect to Port-----------------------------------------------------------//
    printf("Please input the port to connect:");
    scanf("%d", &port);


    strcpy(servIP, "158.83.254.100");             /* First arg: DRACO1 IP address (dotted quad) */

    if((servSock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family      = AF_INET;             /* Internet address family */
    serv_addr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    serv_addr.sin_port        = htons(port); /* Server port */


    if( connect(servSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
            printf("Error: recv() failed or connection closed prematurely\n");      
        
    do{
	for (i = 2; i < bytesRcvd-1; i++){	// Skips '#1 or 0, checks for #
	if (recvBuff[i]=='#'){
	recvBuff[i]='\n';			// Swaps # with enter
	}
}
		
//----------------------------------------------Connected: Loop for User Commands---------------------------------------------//		
        printf("Server_echo:\n%s \n\n",recvBuff);
        printf("Please type to send to server (type QUIT to quit):");
        scanf("%s", sendBuff);
        
        if(count == 0){
		    // File check and creation
		    log = fopen("clientlog.txt","r");
		    if(log == NULL){
		    	
		    	printf("No file found, creating new file\n");
		    	
			} else {
				
				RLine = getline(&r, &RegName, log);
			//printf("\n##### Getting RLine, got %zu ####\n",RLine);
			//printf("\n##### %.7s ####\n",r);
			//printf("\n##### %.7s ####\n",sendBuff);

				// Check registration status and print appropriate message
				if(!(strncmp(r,sendBuff,RLine-1))){
					printf("Welcome Back Registered User\n"); // if you want print sendBuff, or RLine
				} else {
					printf("New user detected please register after login\n");
				}
				// print last login time
				LogLine = getline(&l, &LoginTime, log);
				printf("%s",l);
			}
			if(log != NULL){
				
				fclose(log);
			}
			log = fopen("clientlog.txt","w");
			memcpy(r, sendBuff, strlen(sendBuff)+1);
			count++;
		}
        
        if (send(servSock, sendBuff, sizeof(sendBuff), 0) < 0)
	        printf("Error: send() failed\n");
         sleep(1);

         
        if ( (strcmp (strupr(sendBuff), "QUIT") ==0)){
        	// Get the current time and update the Log Time string for file update
		    time(&l_time);                                                            
		    c_time = localtime(&l_time); 
		    LTime[0]='\0';
		    sprintf(LTime, "\nLast login time: %04d:%02d:%02d:%02d:%02d:%02d\n\n",c_time->tm_year+1900, c_time->tm_mon+1, c_time->tm_mday, c_time->tm_hour, c_time->tm_min, c_time->tm_sec);
			printf("You have disconnected from the server\n\n\n");
			
			UpdateFile(RName, LTime, log);
			
            bytesRcvd = 0;
        } else { 
            memset(&recvBuff, '0', sizeof(recvBuff)); 
           	if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
                printf("Error: recv() failed or connection closed prematurely\n");              
            recvBuff[bytesRcvd]='\0';    
        }
    } while (bytesRcvd>0);
	
    close(servSock); //close the socket
    return 0;
}
