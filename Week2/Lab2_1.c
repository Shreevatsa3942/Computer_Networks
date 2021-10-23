/*1. Write a program using pipe to send a string from parent to 
child inorder to print number of characters and digits in 
the string.*/

//Name: Shreevatsa
//RegNo: 200970093
//Date: 09/09/2021

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int main(){

    int fd[2]; //fd[0] - read; fd[1] - write
    
    if(pipe(fd) == -1){
        printf("\n An Error occured while opening the pipe : ");
        return 1;
    }
    if(fork() > 0){
        close(fd[0]);
        char str[100];

        printf("\nParent Process: ");
        printf("\nEnter the String : ");
        scanf("%s",str);
        // printf("\nEnter a string : ");
        // scanf("%s",str);
        
        int len = strlen(str);
        write(fd[1],&len,sizeof(int));
        write(fd[1],str,sizeof(char)*len);
        close(fd[1]);
    }
    else{
        close(fd[1]);
        printf("\nChild Process: ");
        int len;
        read(fd[0],&len,sizeof(int));
        char str1[len];
        read(fd[0],str1,sizeof(char)*len);
        close(fd[0]);
        int digits = 0,charecters=0;

        for(int i=0;str1[i]!=0;i++){
            if(isdigit(str1[i])) digits++;
            if(isalpha(str1[i])) charecters++;
        }
        printf("\nString : %s",str1);
        printf("\nNumber of digits: %d",digits);
        printf("\nNumber of characters: %d",charecters);
        
        //printf("Hello");
    }
    return 0;
}