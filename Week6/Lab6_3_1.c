/*
3. Write a client-server socket program using TCP. 
Assume that Server has pre-stored information about five Account number, 
PIN and Balance. Client accepts account number, 
pin and withdrawal amount and sends to Server If account holder is valid 
then performs withdrawal operations provided enough balance is available 
otherwise display invalid Accno/PIN or No enough Balance. 
Assume that account can maintain 1000 balance.
*/
//Name: Shreevatsa
//Regno: 200970093

#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h> 
#define SER_PORT 1091
int main(int argc,char* argv){
    int clisock;
    struct sockaddr_in cliaddr;
    cliaddr.sin_port=htons(SER_PORT);
    cliaddr.sin_family=AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clisock = socket(AF_INET,SOCK_STREAM,0);
    if(clisock<0)
    {
    perror("\n SOCKET");
    return 0;
    }
    if(connect(clisock,(struct sockaddr*)&cliaddr,sizeof(cliaddr))<0){
        return 0;
    }

    long accno;
    int pin,amt;

    printf("\nEnter the account : ");
    scanf("%ld",&accno);
    printf("\nEnter the PIN: ");
    scanf("%d",&pin);
    printf("\nEnter the Withdrawal amount: ");
    scanf("%d",&amt);

    write(clisock,&accno,sizeof(long));
    write(clisock,&pin,sizeof(int));
    write(clisock,&amt,sizeof(int));
    

    int balance;
    read(clisock,&balance,sizeof(int));
    if(balance == -1){
        printf("\nInsufficient Balance!!");
    }
    else if(balance == -2)
        printf("\ninvalid Accno/PIN!!");
    else
    printf("\nBalance: %d",balance);

    close(clisock);
    return 0;
}