#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
    int fd1,fd2;
    fd1=open("electricity",O_RDONLY);
    int cust_num,units;
    int years;
    read(fd1,&cust_num,sizeof(int));
    read(fd1,&units,sizeof(int));
    close(fd1);
    float bill=0;
    if(units <= 50){
        bill = units;
    }else if(units<=100){
        bill = units*1.5;
    }
    else if(units<=200){
        bill = units*2;
    }
    else{
       bill = units*3; 
    }
    fd2=open("electricity",O_WRONLY);
    write(fd2,&bill,sizeof(float));
    close(fd2);
    return 0;

}
