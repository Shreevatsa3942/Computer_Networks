#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#define PORT 12003

struct data
{
      char domain[30],ip[20];
};

int main()
{
    int clisock;
    struct data d;
    struct sockaddr_in servaddr;
    servaddr.sin_port=htons(PORT);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;

    if((clisock=socket(AF_INET,SOCK_DGRAM,0))<0)
    {
        perror("SOCKETR\n");
        exit(0);
    }


    printf("CLIENT\n");
    printf("Enter the domain name:\n");
    scanf("%s",&d.domain);

     sendto(clisock,(struct data*)&d,sizeof(struct data),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));
    
     int len=sizeof(servaddr);
	recvfrom(clisock,(struct data*)&d, sizeof(struct data),MSG_WAITALL,(struct sockaddr *)&servaddr,&len);
    
    printf("From server:%s\n",d.ip);
    
    close(clisock);
    return 0;
}

    
       
