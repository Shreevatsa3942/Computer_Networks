#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
    int fd1,fd2;
    fd1=open("maturity_amt",O_RDONLY);
    int dp_amt,tenure;
    int years;
    read(fd1,&dp_amt,sizeof(int));
    read(fd1,&tenure,sizeof(int));
    years = tenure/12;
    close(fd1);
    float mat_amt;
    if(years<=1){
        mat_amt = (float)dp_amt*0.05;
    }
    else if(years<=2){
       mat_amt = (float)dp_amt*0.06; 
    }
    else if(years<=3){
        mat_amt = (float)dp_amt*0.07; 
    }
    else{
        mat_amt = (float)dp_amt*0.08; 
    }
    fd2=open("maturity_amt",O_WRONLY);
    mat_amt+=dp_amt;
    write(fd2,&mat_amt,sizeof(float));
    printf("\nMaturity Amount: %f",mat_amt);
    close(fd2);
    return 0;

}
