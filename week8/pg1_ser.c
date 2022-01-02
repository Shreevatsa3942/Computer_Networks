#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 10025

// Driver code
int main() {
	int sockfd,n;
	char buff[80];
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
    while(1) 
    {
		bzero(buff,sizeof(buff));
        int len=sizeof(cliaddr);
        recvfrom(sockfd,(char *)buff,sizeof(buff),MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);
		printf("From client: %sTo client : ", buff);
		bzero(buff,sizeof(buff));
		n = 0;
		while ((buff[n++] = getchar()) != '\n');
        sendto(sockfd,(const char *)buff,sizeof(buff),MSG_CONFIRM,(const struct sockaddr *)&cliaddr,len);
        if (strncmp("end", buff, 3) == 0) 
        {
			printf("Server Exit...\n");
			break;
		}
	}
	return 0;
}