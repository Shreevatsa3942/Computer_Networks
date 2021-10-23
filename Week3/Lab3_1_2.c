#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h> 
#include<string.h>


int main(){
    int fd = open("isPallindrome",O_RDONLY);
    int n;
    read(fd,&n,sizeof(int));
    char str[n];
    char msg[10];
    read(fd,str,sizeof(char)*n);
    close(fd);
    for(int i=0;i < n/2 ;i++){
        if(str[i] != str[n-i-1]){
            //printf("NO");
             printf("\nNot Pallindrome!!\n");
            strcpy(msg,"NO");
            msg[2]='\0';
            break;
        }
    }
    if(strlen(msg)<=0){
    strcpy(msg,"YES");
    msg[3]='\0';
    printf("\nPallindrome!!\n");
    }
    
    int fd2 = open("isPallindrome",O_WRONLY);
    int len=strlen(msg);
    write(fd2,&len,sizeof(int));
    write(fd2,msg,len);
    close(fd2);
    return 0;
}
