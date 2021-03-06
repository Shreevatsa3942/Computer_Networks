#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"
#define PORT 4447


struct data{
    int a,b,res;
    char c;
};
  
    int main(int argc, char**argv) {  
    struct data d;
    struct sockaddr_in addr, cl_addr;  
    int sockfd, ret;  
    struct hostent * server;
    char * serverAddr;

    if (argc < 2) 
    {
      printf("usage: client < ip address >\n");
      exit(1);  
     }

     serverAddr = argv[1]; 
     
     sockfd = socket(AF_INET, SOCK_STREAM, 0);  
     if (sockfd < 0) 
    {  
      printf("Error creating socket!\n");  
      exit(1);  
     }  
     printf("Socket created...\n");   

     memset(&addr, 0, sizeof(addr));  
     addr.sin_family = AF_INET;  
     addr.sin_addr.s_addr = inet_addr(serverAddr);
     addr.sin_port = PORT;     

     ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
     if (ret < 0) 
    {  
      printf("Error connecting to the server!\n");  
      exit(1);  
     }  
     printf("Connected to the server...\n");  


    printf("Enter the operand 1:");
    scanf("%d",&d.a);
    printf("Enter the operand 2:");
    scanf("%d",&d.b);
    printf("Enter the operator:");
    scanf("%s",&d.c);

    ret = sendto(sockfd, &d,sizeof(struct data), 0, (struct sockaddr *) &addr, sizeof(addr));  
      if (ret < 0) {  
       printf("Error sending data!\n");  
      }
      if((recvfrom(sockfd, &d,sizeof(struct data), 0, NULL, NULL))<0)
       {  
         printf("Error receiving data!\n");    
      } 
       else
     {
           printf("Received: ");
           printf("%d",d.res);  
        printf("\n");
      }  
 
 
 return 0;    
}  

