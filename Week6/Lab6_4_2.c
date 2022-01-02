#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<math.h>

#define SER_PORT 19021

int main(int argc,char *argv){
    int newsock,sersock;
    struct sockaddr_in seraddr;
	struct sockaddr_in cliinfo;
	socklen_t csize=sizeof(cliinfo);
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(SER_PORT);
	seraddr.sin_addr.s_addr=htonl(INADDR_ANY);

    sersock = socket(AF_INET,SOCK_STREAM,0);
    bind(sersock,(struct sockaddr *)&seraddr,sizeof(seraddr));
    listen(sersock,1);
    newsock=accept(sersock,(struct sockaddr*)&cliinfo,&csize);
    printf("\n now connected to %s\n",inet_ntoa(cliinfo.sin_addr));

    int a,b,c;
    read(newsock,&a,sizeof(int));
    read(newsock,&b,sizeof(int));
    read(newsock,&c,sizeof(int));
    
    double x1 = (double)(-b + sqrt((b*b)-(4*a*c)))/(2*a);
    double x2 = (double)(-b - sqrt((b*b)-(4*a*c)))/(2*a);
    
    write(newsock,&x1,sizeof(double));
    write(newsock,&x2,sizeof(double));
    
    printf("\n%lf ",x1);
    close(newsock);
    close(sersock);
    return 0;
}