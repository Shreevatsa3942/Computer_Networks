/*2. Write client-server program using named pipes. 
Client accepts UserName, password from user and passes them to 
server for authentication. Server has pre-stored  
username and passwords and it compares username and 
passwords and returns message -Welcome  <userName> or 
Login Access denied.
*/

//Name: Shreevatsa
//RegNo: 200970093
//Date: 23-09-2021

#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
int main(){

    int fd1,fd2;
    char usrname[50];
    char pass[50];

    
    
    if(mkfifo("login_Validation",S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)==-1){
        if(errno != EEXIST){
            printf("could not create named pipe!!");
            return 0;
        }
    }
    printf("\nEnter username: ");
    scanf("%s",usrname);
    //strcat(usrname,"\0");
    printf("\nEnter password: ");
    scanf("%s",pass);
    //strcat(pass,"\0");
    fd1 = open("login_Validation",O_WRONLY);

    int len1=strlen(usrname);
    usrname[len1] = '\0';
    int len2 = strlen(pass);
    pass[len2] = '\0';
    write(fd1,&len1,sizeof(int));
    write(fd1,&len2,sizeof(int));
    if(write(fd1,usrname,strlen(usrname))<0){
        printf("Writing username failed!!");
        return 0;
    }
    if(write(fd1,pass,strlen(pass))<0){
        printf("Writing password failed!!");
        return 0;
    }
    close(fd1);
    char msg[50];
    
    fd2 = open("login_Validation",O_RDONLY);
    int msglen;
    read(fd2,&msglen,sizeof(int));
    read(fd2,msg,msglen);
    msg[msglen] = '\0';
    printf("%s\n",msg);
    close(fd2);
    return 0;
}