/*4.Write client-server program using named pipes. 
Client accepts - electricty customer number and number of 
units consumed.
Server calculates the bill by applying different rate for 
different slabs of units consumed.
	0- 50 units @ 1/- per unit.
	51-100 units @1.5/- per unit.
	101-200 units @ 2/- per unit.
	>200 units @ 3/- per unit
*/

//Name: Shreevatsa
//Regno: 200970093

#include<stdio.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
    int fd1,fd2;
    if(mkfifo("electricity",0660)==-1){
        if(errno != EEXIST){
            printf("could not create named pipe!!");
            return 0;
        }
    }

    int cust_num,units;

    printf("\nEnter the Customer Number : ");
    scanf("%d",&cust_num);

    printf("\nEnter the Units Consumed : ");
    scanf("%d",&units);


    fd1 = open("electricity",O_WRONLY);
    write(fd1,&cust_num,sizeof(int));
    write(fd1,&units,sizeof(int));
    close(fd1);

    fd2 = open("electricity",O_RDONLY);
    float bill;
    read(fd2,&bill,sizeof(float));

    printf("\nBill Amount: %.2f Rs",bill);
    close(fd2);

    return 0;
}