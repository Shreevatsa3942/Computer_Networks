/*4. Write a client server program using message queue to book multiplex tickets. 
Assume that there are 5 ticket categories and each category there are 20 tickets. 
Assume that this is pre-stored infornaion and available at server.
From client program, User inputs- Name, Phoneno, Ticket category and Number of tickets and 
passs it to server for ticket.Depending on users input, decrement the number of seats 
in corresponding category, send booking information to client  for dislaying on the screen.*/
//Name:Shreevatsa
//Regno:200970093
//Date: 28-10-2021


#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>

struct multiplex{
    char name[100];
    char phno[10];
    int category;
    int num_tickets;
};
struct booking_info{
    int category;
    int num_tickets;
    int remaining_tickets;
    double billamt;
    char message[100];
};
struct msg_Buffer
{
    long msg_type;
    struct multiplex m;
    struct booking_info b;
    //char msg_text[message.a.n];
    
}message;

void main(){
    key_t key;
    int msgid;

    // key = ftok("array_sort",65);
    key = 1041;

    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1;

    printf("\nWritting Data : ");

    
    printf("\nEnter the Name of the customer : ");
    scanf("%s",message.m.name);
    printf("\nEnter the catogory('1','2','3','4','5') : ");
    scanf("%d",&message.m.category);
     printf("\nEnter the customer phno : ");
    scanf("%s",message.m.phno);
    printf("\nEnter the number of tickets : ");
    scanf("%d",&message.m.num_tickets);
   
    //fgets(message.msg_text,message.a.n,stdin);
    if(msgsnd(msgid,&message,sizeof(message),0))
    printf("\nData sent successfully");

    key = 1042;
    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgrcv(msgid,&message,sizeof(message),1,0);
    printf("\n-------Booking Info-----\n");
    printf("\nCategory: %d ",message.b.category);
    printf("\nNumber of tickets: %d ",message.b.num_tickets);
    printf("\nRemaining Tickets: %d ",message.b.remaining_tickets);
    printf("\nTotal Bill: %lf ",message.b.billamt);
    printf("\nMessage status: %s \n\n",message.b.message);
    
    
    msgctl(msgid, IPC_RMID, NULL);
}