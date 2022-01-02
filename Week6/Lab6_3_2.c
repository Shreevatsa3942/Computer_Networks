#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define SER_PORT 1091
struct bank{
    long accno;
    int pin,balance;
};
int main(int argc,char* argv){
    //Pre-stored information 
    struct bank b[5];
    b[0].accno = 1001;
    b[0].pin = 1234;
    b[0].balance=1000;

    b[1].accno = 1002;
    b[1].pin = 1111;
    b[1].balance=1000;
    
    b[2].accno = 1003;
    b[2].pin = 1897;
    b[2].balance=1000;
    
    b[3].accno = 1004;
    b[3].pin = 1501;
    b[3].balance=1000;
    
    b[4].accno = 1005;
    b[4].pin = 1907;
    b[4].balance=1000;

    int sersock,newsock;
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

    long accno;
    int amt,pin;

    read(newsock,&accno,sizeof(long));
    read(newsock,&pin,sizeof(int));
    read(newsock,&amt,sizeof(int));

    for(int i=0;i<5;i++){
        if(b[i].accno == accno && b[i].pin == pin){
        if((b[i].balance-amt)>0){
            b[i].balance-=amt;
            write(newsock,&b[i].balance,sizeof(int));
            return 0;
        }
        else{
            int invalid = -1;
            write(newsock,&invalid,sizeof(int));
            return 0;
        }
        }
    }
    int invalid = -2;
    write(newsock,&invalid,sizeof(int));
    close(newsock);
    close(sersock); 
    return 0;
}