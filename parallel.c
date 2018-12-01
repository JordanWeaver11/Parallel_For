#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include "my_semaphore.h"


//-----------------------------------THREADS------------------------------------
//array of thread IDs
pthread_t THREADS[2];

void *lower_thread (void *ptr);
void *upper_thread (void *ptr);


//random number generator. generates numbers between and including min and max
int gen_rand(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

//global array of "work" to be done by the threads
const int ARRAY_LENGTH = 10000; //warning: array_LENGTH must be > 2
int WORK_ARRAY[10000];

void do_work(int work_value) {
	/*
	int i = 0;
	for(i = work_value; i > 0; i--) {
		float j = work_value * 1000 / i;
	}
	*/
	usleep(work_value);
}

//----------------------------------START MAIN-----------------------------------
int main()
{
	//INITIALIZE-----------------------------------
	//check for error in array creation
	if(ARRAY_LENGTH <= 2) {
		perror_exit("ERROR: ARRAY_LENGTH must be > 2\n");
	}
	if( (sizeof(WORK_ARRAY)/sizeof(int)) != ARRAY_LENGTH ) {
		perror_exit("ERROR: ARRAY_LENGTH must match length of WORK_ARRAY\n");
	}
	
	void * ptr;
	
	//fill array with random work values
	srand(time(NULL)); //seed random number generator with time
	int i = 0;
	for(i = 0; i < ARRAY_LENGTH; i++) {
		WORK_ARRAY[i] = gen_rand(0, 1000);
	}
	//INITIALIZE-----------------------------------

	//SINGLE THREAD--------------------------------
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	//test single thread time to complete
	for(i = 0; i < ARRAY_LENGTH; i++) {
		do_work(WORK_ARRAY[i]);
		//printf("Single thread, current element: %i, sleeping: %i\n", i, WORK_ARRAY[i]);
	}
	gettimeofday(&t2, NULL);
	//time_elapsed = t2-t1, given in microseconds and seconds
	double elapsed_time = (double) (t2.tv_usec - t1.tv_usec) / 1000000 + (double) (t2.tv_sec - t1.tv_sec);
	printf("1 THREAD\n \tTime elapsed: %f\n", elapsed_time);
	//SINGLE THREAD--------------------------------
	
	//2 THREADS, SINGLE SPLIT----------------------
	//test thread timings based on a single split of the array
	//create threads
	gettimeofday(&t1, NULL);
	pthread_create(&THREADS[0], NULL, lower_thread, (void *) ptr);
	pthread_create(&THREADS[1], NULL, upper_thread, (void *) ptr);
	
	pthread_join(THREADS[0], NULL);
	pthread_join(THREADS[1], NULL);
	gettimeofday(&t2, NULL);
	elapsed_time = (double) (t2.tv_usec - t1.tv_usec) / 1000000 + (double) (t2.tv_sec - t1.tv_sec);
	printf("2 THREADS, SINGLE SPLIT\n \tTime Elapsed: %f\n", elapsed_time);
	//2 THREADS, SINGLE SPLIT----------------------
	
	//2 THREADS, DYNAMIC SPLIT---------------------
	
	//2 THREADS, DYNAMIC SPLIT---------------------
	
	
	return 0;
	
}
//----------------------------------END MAIN--------------------------------------

//lower thread function. started by pthread_create
void *lower_thread (void *ptr) {
	int i = 0;
	for(i = 0; i < ARRAY_LENGTH / 2; i++) {
		do_work(WORK_ARRAY[i]);
		//printf("Lower thread, current element: %i, sleeping: %i\n", i, WORK_ARRAY[i]);
	}
}

//upper thread function. started by pthread_create
void *upper_thread (void *ptr) {
	int i = 0;
	for(i = ARRAY_LENGTH / 2; i < ARRAY_LENGTH; i++) {
		do_work(WORK_ARRAY[i]);
		//printf("Upper thread, current element: %i, sleeping: %i\n", i, WORK_ARRAY[i]);
	}
}
