//Server 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 17004
struct person{
    char panno[20];
    float income,invest[4];
};
struct pan_det{
    char panno[20];
    float advance_tax;
};

void fnc(int sockfd,struct pan_det pan[])
{
    struct person p;
    float res[2]={1,0};
    recv(sockfd,&p,sizeof(p),0);
    float rem_income=p.income-p.invest[0]-p.invest[1]-p.invest[2]-p.invest[3];
    float intrest=0;
    if (rem_income<=500000)
        intrest=0;
    else if(rem_income<=700000)
        intrest=.05;
    else if(rem_income<=1000000)
        intrest=.1;
    else if(rem_income<=1500000)
        intrest=.15;
    else
        intrest=.2;
    float tax=rem_income*intrest;
    res[1]=tax;
    printf("pan no : %s\n",p.panno);
    printf("anual income : %.2f\n",p.income);
    printf("investments :\n\tPPF : %.2f\n\tNSC : %.2f\n\tNPS : %.2f\n\tSIP : %.2f \n",p.invest[0],p.invest[1],p.invest[2],p.invest[3]);
    printf("remaining income after investment : %.2f\n",rem_income);
    printf("tax intrest : %.2f %\t tax ammount : %.2f\n",(intrest*100),tax);
    for(int i=0;i<5;i++)
    {
        if(strcmp(pan[i].panno,p.panno)==0)
        {
            printf("advance paid tax : %.2f\n",pan[i].advance_tax);
            if(tax==pan[i].advance_tax)
            {
                res[0]=0;
                res[1]=0;
            }
            else if(tax>pan[i].advance_tax)
            {
                res[0]=1;
                res[1]=tax-pan[i].advance_tax;
            }
            else
            {
                res[0]=2;
                res[1]=pan[i].advance_tax-tax;
            }
            break;
        }
    }
    send(sockfd,res,sizeof(res),0);
    switch((int)res[0])
    {
        case 0:printf("no tax (sent to client)\n");break;
        case 1:printf("pay tax : %.2f  (sent to client)\n",res[1]);break;
        case 2:printf("get refund : %.2f  (sent to client)\n",res[1]);break;
    }
}


int main(){
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if(sockfd == -1){
        perror("\nSOCKET : ");
        return 0;
    }

    struct sockaddr_in serAddress = {0};
    struct sockaddr_in cliinfo = {0};
    
    serAddress.sin_family = AF_INET;
    serAddress.sin_port = htons(PORT);
    serAddress.sin_addr.s_addr = INADDR_ANY;
    socklen_t csize = sizeof(cliinfo);
    if(bind(sockfd,(struct sockaddr *)&serAddress,sizeof(serAddress))==-1){
        perror("\nBIND: ");
        return 0;
    }
    listen(sockfd,1);

    int newsock;
    newsock = accept(sockfd,(struct sockaddr*)&cliinfo,&csize);
    if(newsock == -1){
        perror("\nACCEPT : ");
        return 0;
    }

    struct pan_det pan[5];
    {
        strcpy(pan[0].panno,"DAT00123");
        pan[0].advance_tax=10000;
        strcpy(pan[1].panno,"DAT00456");
        pan[1].advance_tax=50000;
        strcpy(pan[2].panno,"DAT00789");
        pan[2].advance_tax=5000;
        strcpy(pan[3].panno,"DAT00157");
        pan[3].advance_tax=100000;
        strcpy(pan[4].panno,"DAT00360");
        pan[4].advance_tax=200000;
    }

    fnc(newsock,pan);

    return 0;
}