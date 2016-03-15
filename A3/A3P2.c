
/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 3 - Program 2
* Name: Blake Wrege
* E-mail: blake.j.wrege@wmich.edu
* Submitted: 3/14/2016
*************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>



double sum;
int count = 0;
int n = 268435456;
int nArray[268435456];




int main() {
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);

    for (int j=0;j<n;j++){
        nArray[j] =  j;
    
	}

    for (int i=0;i<n;i++){
        sum=sum+nArray[i];
    
	}
printf("%lf\n",sum);
	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf(" %f", elapsed);
	return 0;
}


