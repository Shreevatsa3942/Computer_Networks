#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 4459

int main(){
    int sockfd;
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serAddress;
    serAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serAddress.sin_port = htons(PORT);
    serAddress.sin_family = AF_INET;

    if(connect(sockfd,(struct sockaddr *) &serAddress , sizeof(serAddress))==-1){
        perror("\nConnection : ");
        return 0;
    }
    
    while (1)
    {
        /* code */
        char buff[1024];
        recv(sockfd,buff,sizeof(buff),0);
        printf("\nMessage : %s",buff);
        if(strncmp(buff,"bye",3)==0)
            break;
        bzero(buff,sizeof(buff));
    }
    // close(sockfd);
    return 0;
}