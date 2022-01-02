#include<stdio.h>  
#include<stdlib.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<string.h>  
#include<netinet/in.h>  
#include<netdb.h>
#define PORT 4447

#define CLADDR_LEN 100

struct data{
    int a,b,res;
    char c;
};
void main() 
{
     struct sockaddr_in addr, cl_addr;
     int sockfd, len, ret, newsockfd;
     struct data d;

     pid_t childpid;
     char clientAddr[CLADDR_LEN];
     
     if((sockfd =socket(AF_INET, SOCK_STREAM, 0))<0)
    {
      printf("Error creating socket!\n");
      exit(1);
     }
     printf("Socket created...\n");
     
     memset(&addr, 0, sizeof(addr));
     addr.sin_family = AF_INET;
     addr.sin_addr.s_addr = INADDR_ANY;
     addr.sin_port = PORT;
     
     if(bind(sockfd,(struct sockaddr *)&addr, sizeof(addr))<0)
     {
      printf("Error binding!\n");
      exit(1);
     }
     printf("Binding done...\n");

     printf("Waiting for a connection...\n");
     listen(sockfd, 5);

     for (;;) { 
      len = sizeof(cl_addr);
      if((newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len))<0)
     {
       printf("connection!\n");
       exit(1);
      }
      printf("Connection accepted...\n");

      inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
      if ((childpid = fork()) == 0) { 

       close(sockfd); 
   

      //for (;;) {
        ret = recvfrom(newsockfd,&d,sizeof(struct data), 0, (struct sockaddr *) &cl_addr, &len);
        if(ret < 0) {
         printf("Error receiving data!\n");  
         exit(1);
        }
        printf("Received data from %s: %d %d\n", clientAddr, d.a,d.b); 
        char c1=d.c;
          switch(c1)
         {
		    case '+': d.res=d.a+d.b;
				    break;
            case '-': d.res=d.a-d.b;
			         break;
	        case '*': d.res=d.a*d.b;
			         break;
		    case '/': d.res=d.a/d.b;
			     break;
        }

        if((sendto(newsockfd, &d,sizeof(struct data), 0, (struct sockaddr *) &cl_addr, len))<0)   
       {  
         printf("Error sending data!\n");  
         exit(1);  
        }  
        printf("Sent data to %s: %d\n", clientAddr,d.res);
      // }
      }

  close(newsockfd);

 }
    
}

