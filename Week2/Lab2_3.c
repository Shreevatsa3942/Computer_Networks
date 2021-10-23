/*3.Write a program using pipe to accept an array
 of integers at parent and pass it to child. 
Child will pick only even numbers and return 
array of even numbers to parent.*/

//Name: Shreevatsa
//RegNo: 200970093
//Date: 09/09/2021

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){

    int fd[2]; //fd[0] - read; fd[1] - write
    if(pipe(fd) == -1){
        printf("\n An Error occured while opening the pipe 1: ");
        return 1;
    }

    if(fork() > 0){
        close(fd[0]);
        
        int arr[100],i,n;
        printf("\nEnter the size of an array : ");
        scanf("%d",&n);
        for(i=0;i<n;i++){
            scanf("%d",&arr[i]);
        }
        write(fd[1],&n,sizeof(int));
        if(write(fd[1],arr,sizeof(int)*n) == -1){
            printf("\n An Error occured while writing : ");
            return 2;
        }
        close(fd[1]);
    }
    else{
        close(fd[1]);
        int n,i,j=0;
        int a[100];
        int result[100];
        read(fd[0],&n,sizeof(int));
        if(read(fd[0],a,sizeof(int)*n)==-1){
            printf("\n An Error occured while reading : ");
            return 3;
        }
        for(i=0;i<n;i++){
            if(a[i]%2 == 0){
                result[j] = a[i];
                j++;
            }
        }
        printf("\nEven Array : ");
        for(i=0;i<j;i++){
            printf("%d ",result[i]);
        }
        close(fd[0]);
    }
    return 0;
}