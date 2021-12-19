//Name: shreevatsa
//Regno: 200970093
//Date: 30-09-2021

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

void main()
{
    key_t key;
    int msgid;

    // key = ftok("array_sort",65);
    key = 1011;

    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgrcv(msgid,&message,sizeof(message),1,0);
    //printf("\n%s\n",message.msg_text);
    // for(int i=0;i<message.a.n;i++){
    //     printf("\n%d",message.a.arr[i]);
    // }
    printf("\nNum1: %d\nNum2: %d\nOperator: %c",message.a.num1,message.a.num2,message.a.op);

    printf("\nArithmetic operation ....");

    switch (message.a.op)
    {
    case '+':
        message.result = message.a.num1+message.a.num2;
        break;
    case '-':
        message.result = message.a.num1-message.a.num2;
        break;
    case 'x':
        message.result = message.a.num1*message.a.num2;
        break;
    case '/':
        message.result = message.a.num1/message.a.num2;
        break;
    default:
        printf("\nInvalid Operator!!");
        return;
    }
    msgctl(msgid, IPC_RMID, NULL);


    key = 1012;
    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgsnd(msgid,&message,sizeof(message),0);
    printf("\nOperation Performed ");
    
}
