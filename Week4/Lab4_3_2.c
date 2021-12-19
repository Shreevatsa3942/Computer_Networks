#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
struct msg_Buffer
{
    long msg_type;
    char str[100];
    //char msg_text[message.a.n];
    char result[100];
}message;

void main()
{
    key_t key;
    int msgid;

    // key = ftok("array_sort",65);
    key = 1031;

    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgrcv(msgid,&message,sizeof(message),1,0);
    //printf("\n%s\n",message.msg_text);
    // for(int i=0;i<message.a.n;i++){
    //     printf("\n%d",message.a.arr[i]);
    // }
    printf("Text: %s\n",message.str);
    msgctl(msgid, IPC_RMID, NULL);

    for(int i=0;message.str[i]!='\0';i++){
        message.result[i] = message.str[i]+4+i;
    }
    key = 1032;
    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgsnd(msgid,&message,sizeof(message),0);
    printf("\nOperation Performed ");
    
}
