//server 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9011

struct Input
{
    int num1,num2;
    char op;
}in1;

int main(){
    int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
    socklen_t csize = sizeof(cliaddr);
	while(1)
    {  
        recvfrom(sockfd,&in1,sizeof(in1),MSG_WAITALL,(const struct sockaddr *)&cliaddr,&csize);
        if(in1.num1==0 || in1.num2==0)
            break;
        double res;
        switch(in1.op)
        {
            case '+':res=in1.num1+in1.num2;break;
            case '-':res=in1.num1-in1.num2;break;
            case '*':res=in1.num1*in1.num2;break;
            case '/':res=in1.num1/in1.num2;break;
            default:res=0;break;
        }
        
        if((sendto(sockfd,&res,sizeof(res),0,(const struct sockaddr *)&cliaddr,csize))==-1){
            perror("Sendto");
        }
        else
            printf("result : %.2lf (sent to client)\n",res);
    }
    return 0;
}