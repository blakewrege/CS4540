
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



int MYTHREADS = 8;
double sum[8];
int count = 0;
int n = 1048576;
int Narray[1048576];




struct params {
	pthread_mutex_t mutex;
	pthread_cond_t done;
	int id;
};

typedef struct params params_t;

void* hello(void* arg) {

	int id;
	/* Lock prevents threads from running into each other  */
	pthread_mutex_lock(&(*(params_t*)(arg)).mutex);

	/* Work.  */
	id = (*(params_t*)(arg)).id;

	while (count < n ) {
		count = count + 1;
		Narray[count] = count;

		//printf("index: %d  value: %d\n", count, Narray[count-1]);
	}





	/* Unlock and signal completion.  */
	pthread_mutex_unlock(&(*(params_t*)(arg)).mutex);
	pthread_cond_signal (&(*(params_t*)(arg)).done);


for(int j = 0; j<MYTHREADS; j++){

if (id == j){

int locMin = floor((double)n*(((double)id)/(double)MYTHREADS));
int locMax = floor((double)n*(((double)id+1)/(double)MYTHREADS));
//printf("%lf ",(double)id/(double)MYTHREADS);
//printf("%lf",(double)(id/MYTHREADS));
//printf("%d start: %d  end: %d \n",id,locMin, locMax);
//printf("%d start: %d  end: %d \n",id,locMin, locMax);
while(locMin < locMax){
locMin++;
sum[id] = sum[id] + Narray[locMin];

}
//printf("%d next start: %d\n",id,locMin);


}
}

	/* After signalling `main`, the thread could actually
	go on to do more work in parallel.  */
}


int main() {
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);
	double finalSum;

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

   for (i=0; i< MYTHREADS ; i++)
   {
	 finalSum = sum[i] + finalSum;
   }
	printf("\n\n%d array sum: %lf\n", count, finalSum);

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf(" %f", elapsed);
	return 0;
}


