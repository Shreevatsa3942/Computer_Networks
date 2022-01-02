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
    serAddress.sin_family = AF_INET;
    serAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serAddress.sin_port = htons(PORT);

    bind(sockfd,(struct sockaddr *) &serAddress, sizeof(serAddress));
    listen(sockfd,1);

    int newsock;
    struct sockaddr_in newAddr;
    socklen_t csize = sizeof(newAddr);
    newsock = accept(sockfd, (struct sockaddr *) &newAddr, &csize);

    while (1)
    {
        /* code */
        char buff[1024];
        int n=0;
        printf("\nEnter message: ");
        while((buff[n++] = getchar())!= '\n');
        send(newsock,buff,sizeof(buff),0);

        if(strncmp(buff,"bye",3)==0)
            break;
        
        bzero(buff,sizeof(buff));
    }
    // close(sockfd);
    // close(newsock);
    return 0;
}