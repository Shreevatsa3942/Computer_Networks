/*2. Write a program to develop Client and server application in which server 
checks whether the word sent by the client is palindrome or not.*/
//Name: Shreevatsa
//Regno: 200970093
//Date: 19-12-2021

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

    struct sockaddr_in serAddress;
    memset(&serAddress,'\0',sizeof(serAddress));

    serAddress.sin_family = AF_INET; //IPv4
    serAddress.sin_port = htons(PORT);
    serAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t csize = sizeof(serAddress);
    char buff[1024];
    printf("\nEnter a String : ");
    scanf("%s",buff);
    
    int flag = sendto(sockfd,(char *)buff,sizeof(buff),0,(struct sockaddr*)&serAddress,csize);
    if(flag == -1)
        perror("Send: ");   

    int result;
    recvfrom(sockfd,&result,sizeof(result),0,(struct sockaddr *)&serAddress,&csize);

    if(result == 1)
        printf("\nPallindrome \n");
    else
        printf("\nNot a Pallindrome\n");

    return 0;
}