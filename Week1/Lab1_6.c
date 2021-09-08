/*Accept two numbers and operator (+,-,*, /) as command line 
arguments. 
Perform numerical operation as per operator in the child 
and display the result*/

//Name:Shreevatsa
//Regno:200970093

#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
void main(int argc,char* argv[]){
int num1,num2;
double res = 0;
char op;
num1 = atoi(argv[1]);
num2 = atoi(argv[2]);
op = *argv[3];

if(fork() == 0){
    printf("\nChild Process:");
    switch (op)
    {
    case '+':
        res = num1+num2;
        break;
    case '-':
        res = num1-num2;
        break;
    case 'x':
        res = num1*num2;
        break;
    case '/':
        res = num1/num2;
        break;
    default:
        printf("\nInvalid Operator!!");
        return;
    }

    printf("Result:%lf",res);
}
printf("\n");
}