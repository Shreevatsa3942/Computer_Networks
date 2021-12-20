/*
1.Write a program  a Client and server application where the client accepts two numbers
 and operator and sends to server.Server calculates accourding to operator and 
 returns result to client. Client displays the result and prompts user 
 to enter inputs for next operation.This has to continiue until user enters 0.
*/

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

#define PORT 17001

struct Input
{
    int num1,num2;
    char op;
}in1;

void accept_input(){
    //Accept two numbers 
    printf("\nEnter two numbers : ");
    scanf("%d%d",&in1.num1,&in1.num2);
    printf("\nEnter the character :");
    scanf("%s",&in1.op);
}

int main(){
    int sockfd;
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serAddress = {0};

    serAddress.sin_family = AF_INET;
    serAddress.sin_port = htons(PORT);
    serAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd,(struct sockaddr*)&serAddress,sizeof(serAddress))){
        perror("\nSOCKET : ");
        return 0;
    }

    while (1)
    {
        /* code */
        accept_input();
        send(sockfd,&in1,sizeof(in1),0);
        if(in1.num1 == 0 || in1.num2 == 0)
            break;
        double result;
        recv(sockfd,&result,sizeof(result),0);
        printf("\nResult : %lf",result);
    }
    
    return 0;
}