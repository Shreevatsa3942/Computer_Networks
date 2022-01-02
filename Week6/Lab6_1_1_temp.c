/*Write a client-server chat socket program using TCP protocol to chat in infinite loop until 
client ends the chat session.*/
//Name: Shreevatsa
//Regno: 200970093
//Date: 18-11-2021
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#define SER_PORT 12002
int main(int count,char*arg[])
{
int a,clisock;
char str[20],str2[20];
bzero(str,sizeof(str));
bzero(str2,sizeof(str2));
struct sockaddr_in cliaddr;
cliaddr.sin_port=htons(SER_PORT);
cliaddr.sin_family=AF_INET;
cliaddr.sin_addr.s_addr=inet_addr(arg[1]);
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

while(1)
{
// free(str);
// free(str2);
printf("\nCLIENT: ");
scanf("%s",str);
fflush(stdin);
write(clisock,str,sizeof(str));
if(!strcmp(str,"BYE")){
    // close(clisock);
    break;
}
read(clisock,str2,sizeof(str2));
printf("\nserver msg:%s",str2);
}
close(clisock);
return 0;
}