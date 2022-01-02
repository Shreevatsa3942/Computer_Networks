/*Write a client-server socket program using TCP. Client accepts an IP address and sends to server. 
Server receives IP address and displays it. Server process the IP address to identify the class of IP address (A, B, C, D, E).
Server sends class and default mask to the client via socket. Client displays the result*/

 //Name:Shreevatsa
 //Regno:200970093
 //Date: 02-12-2021

 #include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define SER_PORT 13002

int main(int count,char*arg[])
{
int a,clisock;
struct sockaddr_in cliaddr;
cliaddr.sin_port=htons(SER_PORT);
cliaddr.sin_family=AF_INET;
cliaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
clisock=socket(AF_INET,SOCK_STREAM,0);
if(clisock<0)
{
perror("\n SOCKET");
return 0;
}
if(connect(clisock,(struct sockaddr*)&cliaddr,sizeof(cliaddr))<0)
{
perror("\n CONNECT");
return 0;
}
printf("\nclient connected to %s",arg[1]);
char str[100];
printf("\nEnter the IP Address: ");
scanf("%s",str);
write(clisock,str,sizeof(str));
char res[100];
read(clisock,res,sizeof(res));
printf("\nIP Address Belongs to : %s",res);
char mask[100];
read(clisock,mask,sizeof(mask));
printf("\nDefault Mask : %s",mask);
close(clisock);
return 0;
}
