//Server 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 19002
int main(){
    int sockfd;
    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in serAddress = {0};
    struct sockaddr_in cliinfo = {0};

    serAddress.sin_family = AF_INET;
    serAddress.sin_port = htons(PORT);
    serAddress.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd,(struct sockaddr*)&serAddress,sizeof(serAddress));
    socklen_t csize = sizeof(cliinfo);

    char buff[1024];
    recvfrom(sockfd,(char *)buff,sizeof(buff),0,(struct sockaddr*)&cliinfo,&csize);
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
    int len = sendto(sockfd,&flag,sizeof(flag),0,(struct sockaddr*)&cliinfo,csize);
    if(len == -1){
        perror("SendTO: ");
    }
    return 0;
}