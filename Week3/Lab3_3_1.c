/*3.Write client-server program using named pipes. 
Client accepts Deposit amount and tenure(in years) 
and passes to server. 
Server has pre stred information about different 
interest rates for different tenures. 
Accordingly server applies appropriate interest rate 
and returns maturity amount and interest earned back to  client.
	0-12 months 5%
	13-24 months 6%
	25-36 months 7%
	>36 months  8%
*/

#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
    int fd1,fd2;
    if(mkfifo("maturity_amt",0660)==-1){
        if(errno != EEXIST){
            printf("could not create named pipe!!");
            return 0;
        }
    }

    int dp_amt,tenure;

    printf("\nEnter the Deposit amt : ");
    scanf("%d",&dp_amt);

    printf("\nEnter the Tunure(in Years) : ");
    scanf("%d",&tenure);


    fd1 = open("maturity_amt",O_WRONLY);
    write(fd1,&dp_amt,sizeof(int));
    write(fd1,&tenure,sizeof(int));
    close(fd1);

    fd2 = open("maturity_amt",O_RDONLY);
    float mat_amt;
    read(fd2,&mat_amt,sizeof(float));

    printf("\nMaturity Amount: %f",mat_amt);
    close(fd2);

    return 0;
}