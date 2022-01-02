#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define SER_PORT 12002
int main()
{
int a,sersock,newsock,n;
char str[25],str2[25];
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
// read(newsock,str,sizeof(str));
// n=a=1;
while(1)
{
    
    // free(str2);
    // free(str);
    read(newsock,str,sizeof(str));
    
    if(!strcmp(str,"BYE")){
        // close(newsock);
        // close(sersock);
        break;
    }
printf("\n client msg:%s",str);
printf("\n server msg:");
//bzero(str2,sizeof(str2));
scanf("%s",str2);
fflush(stdin);
printf("\nMessage: %s",str2);
write(newsock,str2,sizeof(str2));
}
close(newsock);
close(sersock);
return 0;
}