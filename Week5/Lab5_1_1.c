/*1. Write a client-server program using shared memory. 
Client accepts an url and shares it with server using shared memory. 
Server reads shared memory and diplays the URL. Assume that server has some database(array) 
storing URL and corresponding IP address of the server on which web application is hosted. 
Server return the IP address of corrsponding web application to the client using shared memeory 
and client displays the IP address. 
*/

//Name:Shreevatsa
//Regno : 200970093

#include<stdio.h>
#include<sys/shm.h>

int main(){
    key_t key = 1001;
    int shmid = shmget(key,1024,IPC_CREAT|0666);
    
}