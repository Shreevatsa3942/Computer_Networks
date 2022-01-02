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
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	while(1)
    {
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
        int len=sizeof(servaddr);
		while ((buff[n++] = getchar()) != '\n');
		sendto(sockfd,(const char *)buff,sizeof(buff),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));
		bzero(buff, sizeof(buff));
		recvfrom(sockfd,(char *)buff,sizeof(buff),MSG_WAITALL,(struct sockaddr *)&servaddr,&len);
		printf("From Server : %s", buff);
		if ((strncmp(buff, "end", 3)) == 0) 
        {
			printf("Client Exit...\n");
			break;
		}
	}

	close(sockfd);
	return 0;
}
