/*
1.Write two separate C programs (one for server and other for client) using UNIX socket APIs 
and TCP, to implement the File server, which will display the contents of the text file at the 
server side. 
The client program should send the name of the text file to the serve whose contents are to be 
displayed at the sever side. If the file is not present on server side, then the server 
should display a proper error message. Client should continue to send the file names until 
the user enters the string ‘stop’.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 10090

int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("SOCKET");
        return 0;
    }
    struct sockaddr_in serAddress = {0};
    serAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serAddress.sin_family = AF_INET;
    serAddress.sin_port = htons(PORT);

    if(connect(sockfd,(struct sockaddr*)&serAddress,sizeof(serAddress))==-1){
        perror("CONNECT:");
        return 0;
    }
    
    while(1){
        char fname[100];
        printf("\nEnter the filename : ");
        //scanf("%s",fname);
        int n=0;
        while((fname[n++]=getchar())!='\n');
        send(sockfd,(char *)fname,sizeof(fname),0);
        if(strncmp(fname,"stop",4)==0){
            break;
        }
    }
    return 0;
}