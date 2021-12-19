/*
2.Write a client server program using message queue to simulate calculator operations(+,-,*,/ 
between two numbers).Client acccepts two numbers and opertaion to be performed from the user and 
writes to message queue. Server reads from message queue and performs the required operation to 
produce result. The server returns the result to client using message queue in order to display result
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
struct Arithmetic_operation
{
    int num1,num2;
    char op;
}a;

struct msg_Buffer
{
    long msg_type;
    struct Arithmetic_operation a;
    //char msg_text[message.a.n];
    int result;
}message;

void main(){
    key_t key;
    int msgid;

    // key = ftok("array_sort",65);
    key = 1011;

    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1;

    printf("\nWritting Data : ");

    
    printf("\nEnter Two Numbers\n num1 : ");
    scanf("%d",&message.a.num1);
    printf("\n num2 : ");
    scanf("%d",&message.a.num2);
    printf("\nEnter the Arithmetic operator : ");
    scanf("%c",&message.a.op);
    //fgets(message.msg_text,message.a.n,stdin);
    if(msgsnd(msgid,&message,sizeof(message),0))
    printf("\nData sent successfully");

    key = 1012;
    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgrcv(msgid,&message,sizeof(message),1,0);
    printf("%d",message.result);
    msgctl(msgid, IPC_RMID, NULL);
}
