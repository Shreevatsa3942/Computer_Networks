#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
int main(){

    int fd1,fd2;
    
    int len1=0,len2=0;
    
    fd1 = open("login_Validation",O_RDONLY);
    read(fd1,&len1,sizeof(int));
    read(fd1,&len2,sizeof(int));
    char usrname[50];
    char pass[50];
    if(read(fd1,usrname,len1)<0){
        printf("Reading username failed!!");
        return 0;
    }
    if(read(fd1,pass,len2)<0){
        printf("Reading password failed!!");
        return 0;
    }
    usrname[len1] = '\0';
    pass[len2]='\0';
    printf("\nLength: %d",len1);
    printf("\nUsername: %s\n",usrname);
    printf("Password: %s\n",pass);
    
    close(fd1);
    char st_usrname[] = "vatsa";
    char st_pass[] = "1234";

    char msg[50];

    int res = strcmp(usrname,st_usrname);
    printf("%d",res);
    if(strcmp(usrname,st_usrname) == 0 && strcmp(pass,pass) == 0){
        strcpy(msg,"Login Successful !!");
    }
    else{
        strcpy(msg,"Login Failed !!");
    }
    fd2 = open("login_Validation",O_WRONLY);
    int msglen = strlen(msg);
    write(fd2,&msglen,sizeof(int));
    write(fd2,msg,strlen(msg));
    close(fd2);
    return 0;
}