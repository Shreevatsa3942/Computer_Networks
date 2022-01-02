#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>

#define PORT 10090

int main(){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        perror("SOCKET");
        return 0;
    }
    struct sockaddr_in serAddress = {0};
    struct sockaddr_in cliinfo = {0};

    serAddress.sin_port = htons(PORT);
    serAddress.sin_addr.s_addr = INADDR_ANY;
    serAddress.sin_family = AF_INET;
    
    bind(sockfd,(struct sockaddr*)&serAddress,sizeof(serAddress));
    listen(sockfd,1);
    socklen_t csize = sizeof(cliinfo);

    int newsock = accept(sockfd,(struct sockaddr*)&cliinfo,&csize);
    if(newsock == -1){
        perror("ACCEPT:");
        return 0;
    }
    while(1){
        char fname[100];
        recv(newsock,(char *)fname,sizeof(fname),0);

        if(strncmp(fname,"stop",4)==0){
            break;
        }

        printf("\nFilename : %s",fname);

        FILE *fp;
        int len = strlen(fname);
        fname[len] = '\0';
        fp = fopen(fname,"r");
        if(fp == NULL){
            printf("\n----File doesn't exist----\n");
        }
        else{
            printf("\n-----File contents-----\n");
            while(1){
                char c = fgetc(fp);
                if(c == EOF)
                    break;
                printf("%c",c);
            }
        }
        // while(1){
        // char c = fgetc(fp);
        // if(c == EOF)
        //     break;
        // printf("%c",c);
        // }
        // fclose(fp);
        
    }
return 0;
}