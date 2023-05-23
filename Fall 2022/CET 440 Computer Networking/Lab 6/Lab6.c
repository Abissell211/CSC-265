#include "Lab6.h"


int KEY[] = {78, 4, 3, 73, 1, 28, 81, 32, 21, 74, 26, 23, 94, 55, 40, 9, 35, 47, 5, 39, 16, 8, 50, 91, 66, 58, 75, 79, 41, 63, 15, 43, 69, 68, 42, 46, 33, 59, 22, 6, 54, 52, 19, 56, 7 ,77 ,85 ,44 ,20 ,67 ,86 ,14 ,93 ,24 ,62, 83, 30, 12, 90, 37, 84, 76, 72, 25, 10, 18, 89, 87, 71, 49, 92, 57, 88, 60, 65, 31, 27, 64, 17, 36, 45, 61, 82, 11, 29, 38, 53, 34, 2, 13, 51, 0, 80, 48, 70}; 


int main(int argc, char *argv[])
{
    int servSock = 0, n = 0;
    int command_request = 1;
    int reg_request = 1;
    char request[32];
    char recvBuff[RCVBUFSIZE];
    char sendBuff[SNDBUFSIZE];
    char command[20], username[8], password[24];
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
    decrypt(KEY,recvBuff,recvBuff);    // ##################
        
    do{
	for (i = 2; i < bytesRcvd-1; i++){	// Skips '#1 or 0, checks for #
	if (recvBuff[i]=='#'){
	recvBuff[i]='\n';			// Swaps # with enter
	}
}
		
//----------------------------------------------Connected: Loop for User Commands---------------------------------------------//		
        printf("\n[Server]%s \n",recvBuff);
        printf("\n[Client]Please type to send to server (type QUIT to quit):");
	memset(&sendBuff, '0', sizeof(sendBuff)); 
	if (reg_request !=2){
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
					printf("\n[Client]Welcome Back Registered User\n"); // if you want print sendBuff, or RLine
				} else {
					printf("\n[Client]New user detected please register after login\n");
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
	strcpy(request,sendBuff);
	command_request = strcmp (strupr(request), "QUIT");
	reg_request = strcmp (strupr(request), "REGISTER");
	//printf("\n##DID REG_REQUEST, GOT %d \n",reg_request);
	}
	if (reg_request ==2){
		do {
			printf("\nPlease input a password, minimum of 8 characters, with at least 3 of the following 4: Uppercase, Lowercase, Special, numbers \n");
			memset(&sendBuff, '0', sizeof(sendBuff)); 	
			scanf("%s",sendBuff);
			if (!passwordCheck(sendBuff)){
				printf("Invalid Password \n");}
		}while (!passwordCheck(sendBuff));
	
		printf("Password Accepted \n");
		reg_request =1;
	}

	if (reg_request == 0){
		reg_request = 2;
	}
	printf("\n[Client] Encrypting [ %s ] ",sendBuff);
        encrypt(KEY,sendBuff,sendBuff);
	printf("\n[Client] Sending [ %s ] ",sendBuff);
        if (send(servSock, sendBuff, sizeof(sendBuff), 0) < 0)
	        printf("Error: send() failed\n");
         sleep(1);

         
        if ( command_request ==0){
		command_request=1;
        	// Get the current time and update the Log Time string for file update
		    time(&l_time);                                                            
		    c_time = localtime(&l_time); 
		    LTime[0]='\0';
			//printf("\n");
		    sprintf(LTime, "\nLast login time: %04d:%02d:%02d:%02d:%02d:%02d\n\n",c_time->tm_year+1900, c_time->tm_mon+1, c_time->tm_mday, c_time->tm_hour, c_time->tm_min, c_time->tm_sec);
			printf("You have disconnected from the server\n\n\n");
			
			UpdateFile(RName, LTime, log);
			
            bytesRcvd = 0;
        } else { 
	   command_request=1;
            memset(&recvBuff, '0', sizeof(recvBuff)); 
           	if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
               		printf("Error: recv() failed or connection closed prematurely\n");              
            	decrypt(KEY,recvBuff,recvBuff); //################
		recvBuff[bytesRcvd]='\0';    
        }
	//decrypt(KEY,recvBuff,recvBuff);
    } while (bytesRcvd>0);
	
    close(servSock); //close the socket
    return 0;
}
