/*1.Write client-server program using named pipes. 
Client accepts a string and passes to Server through 
a named pipe and server checks the string for pallindrome 
and returns a message - YES or NO to Client.*/

//Name: Shreevatsa
//RegNo: 200970093
//Date: 16/09/2021

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h> 
#include<string.h>


int main(int argc,char* argv[]){
    char str[100];
    //strcpy(str,argv[1]);
    printf("Enter a string : ");
    scanf("%s",str);
    if(mkfifo("isPallindrome",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)==-1){
        if(errno != EEXIST){
            printf("could not create named pipe!!");
            return 0;
        }
    }
    int fd = open("isPallindrome",O_WRONLY);
    
    int len = strlen(str);
    write(fd,&len,sizeof(int));
    write(fd,str,sizeof(char)*len);
    close(fd);

    int fd2 = open("isPallindrome",O_RDONLY);
    
    int n;
    read(fd2,&n,sizeof(int));
    char msg[n];
    read(fd2,msg,n);
    //printf("Hello");
    msg[n] = '\0';
    printf("\nMessage: %s\n",msg);
    //printf("%d",n);
    close(fd2);
    //close(fd2);
    return 0;
}
