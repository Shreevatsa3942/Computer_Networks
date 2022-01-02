#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 10025
struct account
{
    unsigned long int accno;
    int pin;
    float amount;
};
// Driver code
int main() {
	int sockfd;
    struct account acc[5];
    
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
    {
    acc[0].accno=1204560123;
    acc[0].pin=1245;
    acc[0].amount=1000;
    acc[1].accno=1204560765;
    acc[1].pin=1011;
    acc[1].amount=10000;
    acc[2].accno=1204560456;
    acc[2].pin=9586;
    acc[2].amount=2000;
    acc[3].accno=1204560884;
    acc[3].pin=2685;
    acc[3].amount=20000;
    acc[4].accno=1204560945;
    acc[4].pin=7956;
    acc[4].amount=100000;
    }
    struct account a;
    int flag=0;
    char str[100];
    recvfrom(sockfd,&a,sizeof(a),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    for(int i=0;i<5;i++)
    {
        if(acc[i].accno==a.accno)
        {
            if(acc[i].pin==a.pin)
            {
                if((acc[i].amount-a.amount)>=1000)
                {
                    acc[i].amount-=a.amount;
                    sprintf(str,"AMMOUNT DEDUCTED : %.2f\nBALANCE : %.2f ",a.amount,acc[i].amount);
                }
                else
                {
                    strcpy(str,"INSUFICENT BALANCE");
                }
            }
            else
            {
                strcpy(str,"INVALID PIN");
            }
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        strcpy(str,"INVALID ACCOUNT NO");
    }
	sendto(sockfd,str, sizeof(str),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
    printf("status sent\n");
	/*
	len = sizeof(cliaddr); //len is value/resuslt
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
	printf("Hello message sent.\n");
	*/
	return 0;
}

