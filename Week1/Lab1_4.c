/*Write a program to accept an array before forking and 
search the array in child for an element accepted 
and display the result*/

//Name:Shreevatsa
//Regno:200970093

#include<stdio.h>
#include<unistd.h>

int main(){

    int arr[100],n,i,ele;
    printf("\nEnter the size of the array: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    printf("\nEnter the Search Element: ");
    scanf("%d",&ele);
    if(fork() == 0){
        printf("\nChild Process:");
        
        for(i=0;i<n;i++){
            if(arr[i] == ele){
                printf("\nElement Found!! ");
                return 0;
            }
                
        }
        printf("\nElement Not Found!! ");
    }
    printf("\n");
    return 0;
}