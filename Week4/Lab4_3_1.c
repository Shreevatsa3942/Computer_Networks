/*3.Write a client server program using message queue to cypher the text. Client take input a line of 
text from the user and sends to server using message Queue. Server reads text from the message queue
and cypher the text (cypher method- simple one any of your choice) and return cyphered text to Client 
for display.*/
//Name:Shreevatsa
//Regno:200970093
//Date: 28-10-2021


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

void main(){
    key_t key;
    int msgid;

    // key = ftok("array_sort",65);
    key = 1031;

    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1;

    printf("\nWritting Data : ");

    
    printf("\nEnter a String : ");
    scanf("%s",message.str);
    //fgets(message.msg_text,message.a.n,stdin);
    if(msgsnd(msgid,&message,sizeof(message),0))
    printf("\nData sent successfully");

    key = 1032;
    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgrcv(msgid,&message,sizeof(message),1,0);
    printf("\nCypher Text: %s\n",message.result);
    msgctl(msgid, IPC_RMID, NULL);
}