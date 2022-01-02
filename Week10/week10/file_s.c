#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<string.h>

#define ser_port 12006

struct data{
    char file[30],buffer[100];;
};

int main()
{
    int sersock,newsock;
    
	
	struct data d;
  \
    ssize_t r;
   
	struct sockaddr_in seraddr;
	struct sockaddr_in cliinfo;
	socklen_t csize=sizeof(cliinfo);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(ser_port);
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
        recv(newsock,&d,sizeof(struct data),0);
        printf("file name:%s\n",d.file);

       int fd1=open(d.file,O_RDONLY);
        
        r=read(fd1,&d.buffer,sizeof(d.buffer));
        printf("Contents of the file:%s",d.buffer);
      

        send(newsock,&d,sizeof(struct data),0);
    
        
        
        close(newsock);
        close(sersock);
        return 0;
}

