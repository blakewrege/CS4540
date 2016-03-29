
/*************************************************
* Course: CS 4540 – Spring 2016
* Assignment 4 - Program 1
* Name: Blake Wrege
* E-mail: blake.j.wrege@wmich.edu
* Submitted: 3/29/2016
*************************************************/


#include <time.h>
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


/* Set global variables */
int MYTHREADS = 10;
int count = 0;
int n = 10000;
int xArray[10][10000];
int yArray[10][10000];
int a = 5;
int b = 12;
int yMax = 12 * 12;
int recArea = (12 * 12) * (12 - 5);
float threadArray[10];


struct params {
	pthread_mutex_t mutex;
	pthread_cond_t done;
	int id;
};

typedef struct params params_t;

/* Work preformed by each thread */
void* threadWork(void* arg) {
	int count = 0;
	int id;
	/* Lock prevents threads from running into each other  */
	pthread_mutex_lock(&(*(params_t*)(arg)).mutex);

	/* Work.  */
	id = (*(params_t*)(arg)).id;
	/* Sets each array element to it's index */


	/* Unlock and signal completion.  */
	pthread_mutex_unlock(&(*(params_t*)(arg)).mutex);
	pthread_cond_signal (&(*(params_t*)(arg)).done);


	/* After signalling `main`, the threads
	go on to do more work in parallel.  */

	/* loop stores random numbers between parameters for each thread */
	int j;
	for ( j = 0; j < n; j++) {
		xArray[id][j] = (rand() % (b + 1 - a)) + a;
	}
	int k;
	for (k = 0; k < n; k++) {
		yArray[id][k] = rand() % yMax + 1;
	}


	int p;
	/* Counts the number of vertices below the line */
	for ( p = 0; p < n; p++) {
		if ((xArray[id][p]*xArray[id][p]) >	yArray[id][p]) {
			count++;
		}
	}

	/* Calculates each integral estimation and stores into array */ 
	float percentBelow = (float)count / (float)n;
	threadArray[id] = (float)percentBelow * (float)recArea;
	printf("Thread %d: %f \n", id, threadArray[id]);

}


int main()
{
	int x, y, n, i, k, h;
	int xMin, xMax, yMax, nMax;
	time_t t;
	srand((unsigned) time(&t));
	float finalSum;
	float finalAvg;

	pthread_t threads[MYTHREADS];
	params_t params;
	pthread_mutex_init (&params.mutex , NULL);
	pthread_cond_init (&params.done, NULL);

	/* Obtain a lock on the parameter.  */
	pthread_mutex_lock (&params.mutex);

	for (i = 0; i < MYTHREADS; i++) {

		/* Change the parameter (I own it).  */
		params.id = i;

		/* Spawn a thread.  */
		pthread_create(&threads[i], NULL, threadWork, &params);

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


	/* Adds the sum of each thread together for final sum */
	for (i = 0; i < MYTHREADS ; i++)
	{
		finalSum = threadArray[i] + finalSum;
	}
	/* Calculates the average among threads and displays */
	finalAvg = finalSum / MYTHREADS;
	printf("Thread Average: %f", finalAvg);



	return 0;
}
