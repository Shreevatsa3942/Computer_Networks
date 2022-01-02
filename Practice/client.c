#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define PORT 1001
struct input{
    int num1,num2;
    char op;
}in1;
int main(){
    int sockfd;
    struct sockaddr_in cliaddr;
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(PORT);
    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("SOCKET: ");
        return 0;
    }
    if(connect(sockfd,(struct sockaddr*)&cliaddr,sizeof(cliaddr))==-1){
        printf("\nNot Connected !!");
        return 0;
    }

    //code

    printf("\nEnter two numbers : ");
    scanf("%d%d",&in1.num1,&in1.num2);
    printf("\nEnter the operator: ");
    scanf("%s",&in1.op);

    write(sockfd,&in1,sizeof(in1));
    close(sockfd);
    return 0;
}