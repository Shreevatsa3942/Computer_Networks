/*Program:Write a program to demonstrate the concept of 
parent & child processes using fork() system call 
in which the parent reads a file name from the keyboard and 
child process uses the file name and reads first 10 characters 
from the file.*/

//Name:Shreevatsa
//RegNo:200970093

#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char* argv[]){
    char filename[50];
    int count=0;
    int call,fd;
    char buffer[1020];    
    //strcpy(filename,argv[1]);

    if(fork()){
        printf("\nParent Process: FileName Reading:\n");
        //printf("\nfileName:");
        //scanf("%s",filename);
        strcpy(filename,argv[1]);
        printf("\nfileName: %s\n",filename);
    }
    else{
        printf("\nChild Process: FileContent Reading:\n");
        strcpy(filename,argv[1]);
        printf("\nfileName: %s\n",filename);
        fd = open(filename,O_RDONLY);
        if(fd == -1){
         //if file doesn't exist
        printf("\nFile Doesn\'t Exist!!");
        close(fd);
        return 0;
        //exit(0);
        }   
        while(read(fd,buffer,1) && count<10){
            printf("\n%c",buffer[0]);
            count++;
        }
        close(fd);
    }

    return 0;
}