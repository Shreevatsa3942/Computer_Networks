//Server 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 17004
int main(){
    int sockfd;
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serAddress = {0};
    struct sockaddr_in cliinfo = {0};

    serAddress.sin_family = AF_INET;
    serAddress.sin_port = htons(PORT);
    serAddress.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd,(struct sockaddr*)&serAddress,sizeof(serAddress));
    listen(sockfd,1);
    socklen_t csize = sizeof(cliinfo);
    int newsock;
    newsock = accept(sockfd,(struct sockaddr*)&cliinfo,&csize);
    char buff[1024];
    recv(newsock,(char *)buff,sizeof(buff),0);
    printf("\nString : %s",buff);
    
    //Check the string is pallindrome or not 
    int str_len = strlen(buff);
    int flag = 1;
    for(int i=0;i<str_len/2;i++){
        if(buff[i] != buff[str_len-i-1]){
            flag = 0;
            break;
        }
    }

    //return result
    int len = send(newsock,&flag,sizeof(flag),0);
    if(len == -1){
        perror("SendTO: ");
    }
    return 0;
}