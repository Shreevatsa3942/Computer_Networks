/*Write a program to accept an array before forking 
and sort the array in child and display.*/
//Name:Shreevatsa
//Regno:200970093

#include<stdio.h>
#include<unistd.h>

int main(){

    int arr[100],n,i,j,tmp;
    printf("\nEnter the size of the array: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    if(fork() == 0){
        printf("\nChild Process:");

        for(i=0;i<n-1;i++){
            for(j=i+1;j<n;j++){
                if(arr[i]>arr[j]){
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                }
            }
        }

        printf("\nSorted Array: ");
        for(i=0;i<n;i++){
            printf(" %d",arr[i]);
        }
    }
    printf("\n");
    return 0;
}