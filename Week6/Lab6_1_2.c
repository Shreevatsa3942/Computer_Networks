#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define SER_PORT 12004
int main()
{
	int a,sersock,newsock,n;
	char str[100],str2[100];
	bzero(str,sizeof(str));
	bzero(str2,sizeof(str2));

	struct sockaddr_in seraddr;
	struct sockaddr_in cliinfo;
	socklen_t csize=sizeof(cliinfo);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(SER_PORT);
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	if((sersock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("\n socket");
		exit(0);
	}
	if(bind(sersock,(struct sockaddr *)&seraddr,sizeof(seraddr))<0)
	{
		perror("\nBIND");
		exit(0);
	}
	if(listen(sersock,1)<0)
	{
		perror("\n LISTEN");
	}
	if((newsock=accept(sersock,(struct sockaddr *)&cliinfo,&csize))<0)
	{
		perror("\n ACCEPT");
		exit(0);
	}
	else
		printf("\n now connected to %s\n",inet_ntoa(cliinfo.sin_addr));

	while(1)
	{
	
	       bzero(str, 10); 

		
		read(newsock, str, sizeof(str)); 
		str[sizeof(str)-1]='\0';
		
		printf("SERVER : From client received: %s \n ", str); 
		//printf("\n\t sizeof(str) =%ld \n",sizeof(str));
		bzero(str2, 10); 
		n = 0; 
		
		printf("SERVER: Enter the string to Send to Client : "); 
		while ((str2[n++] = getchar()) != '\n') 
			; 
		//scanf("%[^\n]",str2);
		
		write(newsock, str2, sizeof(str2)); 
		//printf("\n\t sizeof(str2) =%ld \n",sizeof(str2));
		
		if (strncmp("bye", str2, 3) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	
	
	/*
	    bzero(str,25);
	    read(newsock,str,sizeof(str));
	    printf("\n Server Reads( From Client) msg:%s\n",str);
	  	if (strncmp("BYE", str, 3) == 0) 
	  	{ 
				printf("Server Exit...\n"); 
				break; 
		} 
	    
		


		//scanf("%[^\n]",str2);
		bzero(str2,25); 
		int n=0;
		while ((str2[n++] = getchar()) != '\n') 
					; 

		write(newsock,str2,sizeof(str2));
		printf("\nServer Writes(To Client): %s",str2);*/
		}
	close(newsock);
	close(sersock);
	return 0;
}
