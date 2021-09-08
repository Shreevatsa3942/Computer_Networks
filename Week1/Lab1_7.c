#include<stdio.h>
#include<unistd.h>

void main(){
    int num,i;
    printf("\nEnter an integer value:");
    scanf("%d",&num);

    if(fork() == 0){
        printf("\nChild Process:\nMultiplication table of %d\n",num);
        for(i=1;i<=20;i++){
            printf("\n%d * %d = %d",num,i,(num*i));
        }
    }
}