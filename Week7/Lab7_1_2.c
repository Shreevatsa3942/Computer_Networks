#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 17001

struct Input
{
    int num1,num2;
    char op;
}in1;

int main(){
    int sockfd;
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serAddress = {0};
    struct sockaddr_in cliinfo = {0};
    
    serAddress.sin_family = AF_INET;
    serAddress.sin_port = htons(PORT);
    serAddress.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd,(struct sockaddr*)&serAddress,sizeof(serAddress));
    listen(sockfd,1);
    socklen_t csize = sizeof(cliinfo);
    int newsock = accept(sockfd,(struct sockaddr*)&cliinfo,&cliinfo);
    if(newsock == -1)
        perror("\nACCEPT : ");
    
    

    while(1){
        recv(newsock,&in1,sizeof(in1),0);
        if(in1.num1 == 0 || in1.num2 == 0)
            break;
        double res;
        res = 0;
        switch(in1.op)
        {
            case '+':res=in1.num1+in1.num2;break;
            case '-':res=in1.num1-in1.num2;break;
            case '*':res=in1.num1*in1.num2;break;
            case '/':res=in1.num1/in1.num2;break;
            default:res=0;break;
        }
        send(newsock,&res,sizeof(res),0);
        printf("\nCalculated Result Sent !!");
    }
    return 0;

}