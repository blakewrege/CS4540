
/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 3 - Problem 1
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


// struct timespec start, finish;
// - 2 -
// double elapsed;
// clock_gettime(CLOCK_MONOTONIC, &start);
// /* some of your code here */

int MYTHREADS = 2;
int sum = 0;
int n = 1048576;



struct params {
	pthread_mutex_t mutex;
	pthread_cond_t done;
	int id;
};

typedef struct params params_t;

void* hello(void* arg) {

	int id;
	/* Lock.  */
	pthread_mutex_lock(&(*(params_t*)(arg)).mutex);

	/* Work.  */
	id = (*(params_t*)(arg)).id;

	float arrnum = floor(n/MYTHREADS);


	sum = sum+1;

	// if (id == 0) {
	// 	printf("BOB\n");
	// 	sum = sum + 1;
	// } else {
	// 	sum = sum + 2;
	// 	printf("JOE\n");
	// }

	/* Unlock and signal completion.  */
	pthread_mutex_unlock(&(*(params_t*)(arg)).mutex);
	pthread_cond_signal (&(*(params_t*)(arg)).done);

	/* After signalling `main`, the thread could actually
	go on to do more work in parallel.  */
}


int main() {

	pthread_t threads[MYTHREADS];
	params_t params;
	pthread_mutex_init (&params.mutex , NULL);
	pthread_cond_init (&params.done, NULL);

	/* Obtain a lock on the parameter.  */
	pthread_mutex_lock (&params.mutex);

	int i;
	for (i = 0; i < MYTHREADS; i++) {

		/* Change the parameter (I own it).  */
		params.id = i;

		/* Spawn a thread.  */
		pthread_create(&threads[i], NULL, hello, &params);

		/* Give up the lock, wait till thread is 'done',
		then reacquire the lock.  */
		pthread_cond_wait (&params.done, &params.mutex);
	}

	for (i = 0; i < MYTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	/* Destroy all synchronization primitives.  */
	pthread_mutex_destroy (&params.mutex);
	pthread_cond_destroy (&params.done);
	/* prints out the sum */
	printf("\n%d", sum);
	return 0;
}

// clock_gettime(CLOCK_MONOTONIC, &finish);
// elapsed = (finish.tv_sec - start.tv_sec);
// elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;