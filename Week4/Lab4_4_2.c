
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
struct multiplex{
    char name[100];
    char phno[10];
    int category;
    int num_tickets;
};
struct booking_info{
    char category;
    int num_tickets;
    int remaining_tickets;
    double billamt;
    char message[100];
};
struct stored_info{
    int cat1;
    int cat2;
    int cat3;
    int cat4;
    int cat5;
    
};
struct msg_Buffer
{
    long msg_type;
    struct multiplex m;
    struct booking_info b;
    //char msg_text[message.a.n];
    
}message;


void main()
{
    struct stored_info st1;
    st1.cat1=20;
    st1.cat2=20;
    st1.cat3=20;
    st1.cat4=20;
    st1.cat5=20;
    
    key_t key;
    int msgid;

    // key = ftok("array_sort",65);
    key = 1041;

    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgrcv(msgid,&message,sizeof(message),1,0);
    //printf("\n%s\n",message.msg_text);
    // for(int i=0;i<message.a.n;i++){
    //     printf("\n%d",message.a.arr[i]);
    // }
    msgctl(msgid, IPC_RMID, NULL);
    printf("\nName: %s",message.m.name);   
    message.b.category = message.m.category;
    switch (message.m.category)
    {
    case 1:
        st1.cat1-=message.m.num_tickets;
        if(st1.cat1 < 0){
            strcpy(message.b.message,"Seats are insufficient");
            message.b.num_tickets=message.m.num_tickets;
            //printf("\nSeats: %d ",st1.cat1);
        }
        else{
            message.b.num_tickets=message.m.num_tickets;
            message.b.remaining_tickets=st1.cat1;
            message.b.billamt = message.b.num_tickets*150;
            strcpy(message.b.message,"Booking successfull");
        }
        break;
    case 2:
        st1.cat2-=message.m.num_tickets;
        if(st1.cat2 < 0){
            strcpy(message.b.message,"Seats are insufficient");
            message.b.num_tickets=message.m.num_tickets;
        }
        else{
            message.b.num_tickets=message.m.num_tickets;
            message.b.remaining_tickets=st1.cat2;
            message.b.billamt = message.b.num_tickets*150;
            strcpy(message.b.message,"Booking successfull");
        }
        break;
    case 3:
        st1.cat3-=message.m.num_tickets;
        if(st1.cat3 < 0){
            strcpy(message.b.message,"Seats are insufficient");
            message.b.num_tickets=message.m.num_tickets;
        }
        else{
            message.b.num_tickets=message.m.num_tickets;
            message.b.remaining_tickets=st1.cat3;
            message.b.billamt = message.b.num_tickets*150;
            strcpy(message.b.message,"Booking successfull");
        }
        break;
    case 4:
        st1.cat4-=message.m.num_tickets;
        if(st1.cat4 < 0){
            strcpy(message.b.message,"Seats are insufficient");
            message.b.num_tickets=message.m.num_tickets;
        }
        else{
            message.b.num_tickets=message.m.num_tickets;
            message.b.remaining_tickets=st1.cat4;
            message.b.billamt = message.b.num_tickets*150;
            strcpy(message.b.message,"Booking successfull");
        }
        break;
    case 5:
        st1.cat5-=message.m.num_tickets;
        if(st1.cat5 < 0){
            strcpy(message.b.message,"Seats are insufficient");
            message.b.num_tickets=message.m.num_tickets;
        }
        else{
            message.b.num_tickets=message.m.num_tickets;
            message.b.remaining_tickets=st1.cat5;
            message.b.billamt = message.b.num_tickets*150;
            strcpy(message.b.message,"Booking successfull");
        }
        break;
    default: printf("\ninvalid Choice!!");
        break;
    }

    key = 1042;
    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgsnd(msgid,&message,sizeof(message),0);
    printf("\nOperation Performed ");
    
}
