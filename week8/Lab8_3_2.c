//server 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 19001

int main(){
    int sockfd;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1){
        perror("\nSOCKET: ");
        return 0;
    }
    struct sockaddr_in servAddress,cliinfo;
    memset(&servAddress,'\0',sizeof(servAddress));
    memset(&cliinfo,'\0',sizeof(cliinfo));
    
    servAddress.sin_family=AF_INET;
    servAddress.sin_port = htons(PORT);
    servAddress.sin_addr.s_addr = INADDR_ANY;

    socklen_t csize=sizeof(cliinfo);

    //binding 
    bind(sockfd,(struct sockaddr*)&servAddress,sizeof(servAddress));
    
    //Receive 
    while (1)
    {
        /* code */
        char buffer[1024],buffer2[1024];
        bzero(buffer,sizeof(buffer));
        bzero(buffer2,sizeof(buffer2));
        int n=0;
        recvfrom(sockfd,(char *)buffer,sizeof(buffer),0,(struct sockaddr*)&cliinfo,&csize);
        printf("\nClient Message : %s",buffer);
        if(strncmp(buffer,"bye",3)==0)
            break;
        printf("\nServer Message : ");
        while((buffer2[n++]=getchar())!='\n');
        int len = sendto(sockfd,(char *)buffer2,sizeof(buffer),0,(struct sockaddr*)&cliinfo,csize);
        if(len == -1){
            perror("\nFailed to send!");
        }
        
    }
    
    return 0;
}