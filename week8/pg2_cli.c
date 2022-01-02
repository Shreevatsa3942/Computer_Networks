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
	
    //solution 
    char buff[80];
	struct ip_sol res;
	bzero(buff,sizeof(buff));
	printf("Enter the ip adress : ");
	scanf("%s",buff);
	sendto(sockfd,(const char *)buff,sizeof(buff),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));
    int len=sizeof(servaddr);
	recvfrom(sockfd,(struct ip_sol *)&res, sizeof(res),MSG_WAITALL,(struct sockaddr *)&servaddr,&len);
	printf("class : %s\ndefault mask : %s\n",res.class,res.mask);

	/*int  len;
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
    */
	close(sockfd);
	return 0;
}
