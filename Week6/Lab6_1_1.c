/*Write a client-server chat socket program using TCP protocol to chat in infinite loop until client ends the chat session.*/
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
#define SER_PORT 12004
int main(int count,char*arg[])
{
int a,clisock;
char str[100],str2[100];
bzero(str,sizeof(str));
bzero(str2,sizeof(str2));
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
int n;
while(1)
{
	        bzero(str, sizeof(str));
	        
		printf("CLIENT:Enter the string to Send to Server : "); 
		n = 0; 
		while ((str[n++] = getchar()) != '\n') 
			; 
		//scanf("%[^\n]",str);
		write(clisock, str, sizeof(str)); 
		//printf("\n\t  sizeof(str)=%ld:\n ",sizeof(str));  
		bzero(str2, sizeof(str2)); 
		read(clisock, str2, sizeof(str2));
		// printf("\n\t  sizeof(str2)=%ld:\n ",sizeof(str2)); 
		str2[sizeof(str2)-1]='\0';
		printf("CLIENT:From Server Received : %s", str2); 
		if ((strncmp(str2, "bye", 3)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	 
	 
	 
/*	 
	 bzero(str,25);
	
	int n=0;
	
	while ((str[n++] = getchar()) != '\n') 
			; 
	//scanf("%[^\n]",str);
	
	write(clisock,str,sizeof(str));
	if (strncmp("BYE", str, 3) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	bzero(str2,25);
	read(clisock,str2,sizeof(str2));
	printf("\nClient Reads(From Server):%s\n",str2);*/
}
close(clisock);
return 0;
}
