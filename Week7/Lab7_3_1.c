/*
3.Write a program to develop Client and server application in which client accepts 
PANNO,Anual income,amountinvestment under headings -PPF,NSC,NPS,SIP(not necessary 
that all the investments has to be done,some of them/all may be 0). 
Display these informations at Server and  Calculate the Taxable income after deducting investments 
from the Annual income. Calulctae the tax to be paid to the goverment according to the following 
criteria.
upto 5 lakh -0%
<5 to 7 lakh -5%
<7 to 10 lakh-10%
>10 to 15 lakh -15%
>15 lakh -20%.
Assume that server has already database contaning-PANNO and Advance_Tax_Deducted.
Depending on the tax calulated & Advance_Tax_Deducted display the message that - 
No Tax  if tax calulated=Advance_Tax_Deducted;
Pay Tax =tax calulated-Advance_Tax_Deducted if tax calulated > Advance_Tax_Deducted;
Get refund = Advance_Tax_Deducted -tax calulated if tax calulated < Advance_Tax_Deducted;
These messages must be sent to Client.
*/

//Name:Shreevatsa
//Regno:200970093

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 17004
struct person{
    char panno[20];
    float income,invest[4];
}p;
void accept_input(){
    printf("enter pan no : ");
    scanf("%s",p.panno);  
    printf("enter anual income : ");
    scanf("%f",&p.income);
    printf("enter investmets on PPF NSC NPS SIP respectively(0 if no investments) :");
    scanf("%f%f%f%f",&p.invest[0],&p.invest[1],&p.invest[2],&p.invest[3]);
    
}
int main(){
    int sockfd ;
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in servAddress = {0};
    servAddress.sin_family = AF_INET;
    servAddress.sin_port = htons(PORT);
    servAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(sockfd,(struct sockaddr*)&servAddress,sizeof(servAddress))==-1){
        perror("CONNECT : ");
        return 0;
    }

    accept_input();
    float res[2]={0,0};
    send(sockfd,&p,sizeof(p),0);
    recv(sockfd,res,sizeof(res),0);
    switch((int)res[0])
    {
        case 0:printf("no tax (from server)\n");break;
        case 1:printf("pay tax : %.2f  (from server)\n",res[1]);break;
        case 2:printf("get refund : %.2f  (from server)\n",res[1]);break;
    }
    
    return 0;
}