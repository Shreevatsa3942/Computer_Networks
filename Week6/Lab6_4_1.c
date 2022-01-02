/*4. Write a client-server socket program using TCP. 
Client accepts and sends coefficients (a, b, c) of a quadratic equation 
to server. Server calculates roots of quadratic equation and 
return roots to client. Client displays the roots of quadratic equation. 
Consider all possibilities of a,b,c values.*/

//Name: Shreevatsa
//Regno: 200970093

#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SER_PORT 19021
int main(int argc,char* argv){
    int clisock;
    struct sockaddr_in cliaddr;
    cliaddr.sin_port=htons(SER_PORT);
    cliaddr.sin_family=AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clisock = socket(AF_INET,SOCK_STREAM,0);
    if(clisock<0)
    {
    perror("\n SOCKET");
    return 0;
    }
    if(connect(clisock,(struct sockaddr*)&cliaddr,sizeof(cliaddr))<0){
        return 0;
    }
    printf("\nEnter the coefficients( A,B,C ): ");
    int a,b,c;
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&c);

    write(clisock,&a,sizeof(int));
    write(clisock,&b,sizeof(int));
    write(clisock,&c,sizeof(int));

    double x1,x2;
    read(clisock,&x1,sizeof(double));
    read(clisock,&x2,sizeof(double));
    
    printf("\nQuadratic Root(x) : %lf or %lf\n",x1,x2);
    close(clisock);
    return 0;
}