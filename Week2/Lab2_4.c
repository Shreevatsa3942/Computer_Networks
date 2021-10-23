/*4.Write a program using pipe to accept details 
of a student such as - RegNo,Mark1,Mark2,Mark3 
and send it to child.
Child will find avarage and accordingly assign 
Gardes(A+,A,B,C,D,E,F- assume some crteria) and 
return grade to Parent*/

//Name: Shreevatsa
//RegNo: 200970093
//Date: 09/09/2021

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

int main(){
    int fd[2]; //fd[0] - read; fd[1] - write
    if(pipe(fd) == -1){
        printf("\n An Error occured while opening the pipe: ");
        return 1;
    }
    int pid = fork();
    if(pid > 0){
        close(fd[0]);
        printf("\nEnter student Details :");
        int regno,m1,m2,m3;
        printf("\nRegistration Number :");
        scanf("%d",&regno);
        write(fd[1],&regno,sizeof(int));
        printf("\nMark 1 :");
        scanf("%d",&m1);
        write(fd[1],&m1,sizeof(int));
        printf("\nMark 2 :");
        scanf("%d",&m2);
        write(fd[1],&m2,sizeof(int));
        printf("\nMark 3 :");
        scanf("%d",&m3);    
        write(fd[1],&m3,sizeof(int));

        close(fd[1]); 
    }
    else{
        close(fd[1]);
        int regno,m1,m2,m3;
        float avg;
        char grade[3];
        read(fd[0],&regno,sizeof(int));
        read(fd[0],&m1,sizeof(int));
        read(fd[0],&m2,sizeof(int));
        read(fd[0],&m3,sizeof(int));
        
        avg = (m1+m2+m3)/3.0;
        if(avg > 90)
            strcpy(grade,"A+");
        else if(avg > 80)
            strcpy(grade,"A");
        else if(avg > 70)
            strcpy(grade,"B");
        else if(avg > 60)
            strcpy(grade,"C");
        else if(avg > 50)
            strcpy(grade,"D");
        else if(avg > 40)
            strcpy(grade,"E");
        else
            strcpy(grade,"F-");

        printf("\nAverage: %f",avg);
        printf("\nGrade: %s",grade);  
        close(fd[0]); 
    }
    return 0;
}