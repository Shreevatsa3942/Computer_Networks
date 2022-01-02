#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 10025

//structure to pass result
struct ip_sol
{
    char class[15];
    char mask[16];
};

// Driver code
int main() {
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
    
    //solution
    char buff[80];
	struct ip_sol res;
	bzero(buff,sizeof(buff));
    int len=sizeof(servaddr);
    recvfrom(sockfd,(char *)buff,sizeof(buff),MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);
	printf("From client: %s\n", buff);
    int n=0;
    int no=0;
    while(buff[n]!='.')
    {
        no=no*10+(buff[n]-'0');
        n++;
    }
    if(no>=0 && no<128)
    {
        strcpy(res.class,"class A");
        strcpy(res.mask,"255.0.0.0");
    }
    else if(no>=128 && no<192)
    {
        strcpy(res.class,"class B");
        strcpy(res.mask,"255.255.0.0");
    }
    else if(no>=192 && no<224)
    {
        strcpy(res.class,"class C");
        strcpy(res.mask,"255.255.255.0");
    }
    else if(no>=224 && no<240)
    {
        strcpy(res.class,"class D");
        strcpy(res.mask,"255.255.255.255");
    }
    else
    {
        strcpy(res.class,"class E");
        strcpy(res.mask,"255.255.255.255");
    }
	sendto(sockfd,(const struct ip_sol *)&res, sizeof(res),MSG_CONFIRM,(const struct sockaddr *)&cliaddr,len);
    close(sockfd);
	return 0;
}

