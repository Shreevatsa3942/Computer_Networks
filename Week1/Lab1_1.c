/*Program: Write a program to copy one file to 
another using file system calls.*/

//Name:Shreevatsa
//RegNo:200970093
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd,fd_dest,fd_create;
    char buffer[1020];
    char filename[50],DestFile[50];
    //long int n1;
    printf("\nEnter the fileName: ");
    scanf("%s",filename);

    
    printf("\nEnter the Destination FileName: ");
    scanf("%s",DestFile);

    //File operations
    //Open file
    fd = open(filename,O_RDONLY);
    fd_dest=open(DestFile,O_WRONLY|O_CREAT,S_IRUSR|S_IRWXU|S_IRWXO|S_IROTH);
    //fd_dest = creat(DestFile,066);
    if(fd == -1){
         //if file doesn't exist
        printf("\nFile Doesn\'t Exist!!");
        close(fd);
        return 0;
        //exit(0);
    }
    else{
    //if file exists
    
    while(read(fd,buffer,1)){
        //printf("%s",buffer);
        write(fd_dest,buffer,1);
        
    }
    printf("Successful copy");
    close(fd);
    close(fd_dest);
    }
    return 0;
}