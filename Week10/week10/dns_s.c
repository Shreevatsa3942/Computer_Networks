#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 12003
struct data{
    char domain[30],ip[20];
};

struct db
{
    char d[30],ad[20];
};

int main()
{
    int sersock;
    struct data d;
    struct db b[5];

    b[0]=(struct db){"www.google.com","8.8.8.8"};
    b[1]=(struct db){"www.amazon.com","205.251.252.0"};
    b[2]=(struct db){"www.flipkart.com","123.8.8.16"};
    b[3]=(struct db){"www.facebook.com","7.7.7.7"};
    b[4]=(struct db){"www.instagram.com","122.0.0.1"};

    struct sockaddr_in servaddr, cliaddr;
	
	
	if ( (sersock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	
	if ( bind(sersock, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

     int len=sizeof(servaddr);
        int j=-1;
     recvfrom(sersock,(struct data*)&d, sizeof(struct data),MSG_WAITALL,(struct sockaddr *)&cliaddr,&len);
        printf("Domain name:%s\n",d.domain);
    for(int i=0;i<5;i++)
    {
        if(strcmp(d.domain,b[i].d)==0)
        {
            j=i;
            printf("SUCCESS\n");
            break;
    
        }
    }
   
    if(j==-1)
    {
        strcpy(d.ip,"Host Not Found\n");
    }
    else
    {
        strcpy(d.ip,b[j].ad);
    }
    sendto(sersock,(struct data*)&d,sizeof(struct data),MSG_CONFIRM,(const struct sockaddr *)&cliaddr,sizeof(cliaddr));
    close(sersock);
    return 0;
}
    
    
    
