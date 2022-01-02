#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>

#define PORT 19001
int main(){
    int sockfd;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd == -1){
        perror("\nSOCKET:");
        return 0;
    }
    struct sockaddr_in servAddress;
    memset(&servAddress,'\0',sizeof(servAddress));

    servAddress.sin_family = AF_INET;
    servAddress.sin_port = htons(PORT);
    servAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    //Writting message
    while(1){
        char buffer[1024],buffer2[1024];
        bzero(buffer,sizeof(buffer));
        bzero(buffer2,sizeof(buffer2));

        int n=0;
        printf("\nClient Message: ");
        while((buffer[n++]=getchar())!='\n');
        //sending message to server 
        int len = sendto(sockfd,(char *)buffer,sizeof(buffer),0,(struct sockaddr*)&servAddress,sizeof(servAddress)); 
        if(len == -1){
            perror("\nFailed to send!");
        }
        if(strncmp(buffer,"bye",3)==0)
            break;
            
        recvfrom(sockfd,(char *)buffer2,sizeof(buffer),0,(struct sockaddr*)&servAddress,sizeof(servAddress));
        printf("Server Message : %s",buffer2);
    }
  
    return 0;
}