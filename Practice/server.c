#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORT 1001

int main(){
    int newsock,sersock;
    struct sockaddr_in seraddr,cliinfo;
    socklen_t csize = sizeof(cliinfo);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(PORT);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    sersock = socket(AF_INET,SOCK_STREAM,0);
    if(sersock == -1){
        perror("\nSOCKET:");
        return 0;
    }

    bind(sersock,(struct sockaddr *)&seraddr,sizeof(seraddr));
    listen(sersock,1);
    newsock = accept(sersock,(struct sockaddr *)&cliinfo,&csize);
    if(newsock == -1){
        perror("\nConnction Error: ");
        return 0;
    }
    else{
        printf("\nConnected!!");
    }
    return 0;
}