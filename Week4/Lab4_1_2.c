//Name: shreevatsa
//Regno: 200970093
//Date: 30-09-2021

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdlib.h>
//#define MAX 5
struct Array
{
    int arr[100];
    int n;
}a;

struct msg_Buffer
{
    long msg_type;
    struct Array a;
    //char msg_text[message.a.n];
}message;

int main()
{
    key_t key;
    int msgid;

    // key = ftok("array_sort",65);
    key = 1001;

    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgrcv(msgid,&message,sizeof(message),1,0);
    //printf("\n%s\n",message.msg_text);
    // for(int i=0;i<message.a.n;i++){
    //     printf("\n%d",message.a.arr[i]);
    // }
    printf("\nArray: ");
    for(int i=0;i<message.a.n;i++){
        printf("%d ",message.a.arr[i]);
    }

    printf("\nSorting ....");

    int temp;
    int i,j;
    for(i=0;i<message.a.n-1;i++){
        for(j=i+1;j<message.a.n;j++){
            if(message.a.arr[i] > message.a.arr[j]){
            temp = message.a.arr[i];
            message.a.arr[i] = message.a.arr[j];
            message.a.arr[j] = temp;
            }
        }
    }
    printf("\nArray: ");
    for(int i=0;i<message.a.n;i++){
        printf("%d ",message.a.arr[i]);
    }
    msgctl(msgid, IPC_RMID, NULL);


    key = 1002;
    msgid = msgget(key,0666|IPC_CREAT);
    message.msg_type = 1; 
    msgsnd(msgid,&message,sizeof(message),0);
    printf("\nSorted Array Sent ");
    return 0;
}
