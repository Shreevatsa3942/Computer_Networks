#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define ser_port 12006

struct data{
    char file[30],buffer[100];
};

int main(int count,char *arg[])
{
    int clisock;
    struct data d;
    struct sockaddr_in cliaddr;
    cliaddr.sin_port=htons(ser_port);
    cliaddr.sin_family=AF_INET;
    cliaddr.sin_addr.s_addr=inet_addr(arg[1]);

    if((clisock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("SOCKET\n");
        exit(0);
    }

    if(connect(clisock,(struct sockaddr*)&cliaddr,sizeof(cliaddr))<0)
    {
        perror("Connect\n");
        exit(0);
    }
    else
        printf("Connected to %s\n",arg[1]);
        printf("Enter the filename:");
        scanf("%s",&d.file);

        send(clisock,&d,sizeof(struct data),0);
         recv(clisock,&d,sizeof(struct data),0);
          printf("From SERVER:%s",d.buffer);

        close(clisock);
        return 0;
}
    
        
