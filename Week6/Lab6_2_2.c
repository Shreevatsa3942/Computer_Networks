#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define SER_PORT 13002
int main()
{
	int a,sersock,newsock,n;

	struct sockaddr_in seraddr;
	struct sockaddr_in cliinfo;
	socklen_t csize=sizeof(cliinfo);
	seraddr.sin_family=AF_INET;//IPV4
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

	char str[100];
    read(newsock,str,sizeof(str));
    printf("IP Address: %s\n",str);
    char *newstr = strtok(str,".");
    // printf("\nIP: %s",newstr);
    int ip = atoi(newstr);
    printf("\nIP: %d",ip);
    char res[100];
	char mask[100];
    if(ip>0 && ip<=127){
        strcpy(res,"Class A");
		strcpy(mask,"255.0.0.0");
	}
    else if(ip>127 && ip<=191){
        strcpy(res,"Class B");
		strcpy(mask,"255.255.0.0");
	}
    else if(ip>191 && ip<=223){
        strcpy(res,"Class C");
		strcpy(mask,"255.255.255.0");
	}
    else if(ip>223 && ip<=239){
        strcpy(res,"Class D");
		strcpy(mask,"-");
	}
    else if(ip>239 && ip<=255){
		strcpy(res,"Class E");
		strcpy(mask,"-");
	}
    else 
        strcpy(res,"Invalid");  
    write(newsock,res,sizeof(res)); 
	write(newsock,mask,sizeof(mask));
	close(newsock);
	close(sersock);
	return 0;
}
