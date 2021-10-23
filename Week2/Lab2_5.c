/*5.Write a program using pipe to accept a matrix 
on nxn and pass it to child. Child will multiply 
each element of user choice to each element return 
new matrix back to to parent. */

//Name: Shreevatsa
//RegNo: 200970093
//Date: 09/09/2021


#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
    int fd[2],fd2[2];
    
    if(pipe(fd) == -1){
        printf("\n An Error occured while opening the pipe 1: ");
        return 1;
    }
    if(pipe(fd2) == -1){
        printf("\n An Error occured while opening the pipe 2 : ");
        return 1;
    }
    int pid = fork();
    if(pid > 0){
        close(fd[0]);
        close(fd2[1]);
        int row=0,col=0;
        printf("\n------Parent process-----\n");        
        printf("\nEnter the size of the matrix: \nrow:");
        scanf("%d",&row);
        printf("\ncol:");
        scanf("%d",&col);
        
        int matrix[row][col],i,j;
        int result[row][col];
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                scanf("%d",&matrix[i][j]);
            }
        }
        write(fd[1],&row,sizeof(int));
        write(fd[1],&col,sizeof(int));
        write(fd[1],matrix,sizeof(int)*row*col);
        close(fd[1]);
        

        if(read(fd2[0],result,sizeof(int)*row*col) == -1){
            printf("\n An Error occured while reading : ");
            return 2;
        }
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                printf("%d ",result[i][j]);
            }
            printf("\n");
        }
        close(fd2[0]);
        
    }
    else{
        close(fd[1]);
        close(fd2[0]);
        
        int row=0,col=0,mul_num=0,i=0,j=0;
        read(fd[0],&row,sizeof(int));
        read(fd[0],&col,sizeof(int));
        int arr[row][col];
        read(fd[0],arr,sizeof(int)*row*col);
        printf("\n------Child process-----\n");
        printf("\nEnter the multiplication number : ");
        scanf("%d",&mul_num);
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                arr[i][j]*=mul_num;
            }
            printf("\n");
        }
        close(fd[0]);
        if(write(fd2[1],arr,sizeof(int)*row*col) == -1){
            printf("\n An Error occured while writing : ");
            return 2;
        }
        
        close(fd2[1]);

    }
    return 0;
}