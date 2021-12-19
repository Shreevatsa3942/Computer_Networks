/*1.Write a program  a Client and server application where the client accepts two numbers 
and operator and sends to server.Server calculates accourding to operator and returns result to client. 
Client displays the result and prompts user to enter inputs for next operation.This has to continiue until user enters 0.*/
//Name: Shreevatsa
//Regno: 200970093
//Date: 15-12-2021

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 9011

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
    int clisock;
    struct sockaddr_in servaddr;
    // Creating socket file descriptor
	if ( (clisock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

    memset(&servaddr, 0, sizeof(servaddr));
    // Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

    //Loop for accepting number and perform operation 
   while(1){
        accept_input();
        sendto(clisock,&in1,sizeof(in1),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));
        if(in1.num1 == 0 || in1.num2 == 0)
            break;
        double result;
        if((recvfrom(clisock,&result,sizeof(result),MSG_WAITALL,(const struct sockaddr *)&clisock,sizeof(clisock)))==-1)
            perror("Recieve From: ");
        printf("\nResult : %.2lf ",result);
        
    }


    return 0;
}