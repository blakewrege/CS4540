
/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 2 - Problem 1
* Name: Blake Wrege
* E-mail: blake.j.wrege@wmich.edu
* Submitted: 2/15/2016
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


// struct timespec start, finish;
// - 2 -
// double elapsed;
// clock_gettime(CLOCK_MONOTONIC, &start);
// /* some of your code here */

// clock_gettime(CLOCK_MONOTONIC, &finish);
// elapsed = (finish.tv_sec - start.tv_sec);
// elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;




void *inc_x(void *x_void_ptr)
{

	/* increment x to 100 */
	int *x_ptr = (int *)x_void_ptr;
	while (++(*x_ptr) < 100);

	printf("x increment finished\n");

	/* the function must return something - NULL will do */
	return NULL;

}

int main()
{

	int x = 0, y = 0;

	/* show the initial values of x and y */
	printf("x: %d, y: %d\n", x, y);

	/* this variable is our reference to the second thread */
	pthread_t inc_x_thread;

	/* create a second thread which executes inc_x(&x) */
	if (pthread_create(&inc_x_thread, NULL, inc_x, &x)) {

		fprintf(stderr, "Error creating thread\n");
		return 1;

	}
		if (pthread_create(&inc_x_thread, NULL, inc_x, &x)) {

		fprintf(stderr, "Error creating thread\n");
		return 1;

	}
	/* increment y to 100 in the first thread */
	while (++y < 100);

	printf("y increment finished\n");

	/* wait for the second thread to finish */
	if (pthread_join(inc_x_thread, NULL)) {

		fprintf(stderr, "Error joining thread\n");
		return 2;

	}

	/* show the results - x is now 100 thanks to the second thread */
	printf("x: %d, y: %d\n", x, y);
}