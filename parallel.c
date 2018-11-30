#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <stdio.h>
#include <stdint.h>
#include <semaphore.h>
#include <time.h>

//-----------------------------------SEMAPHORES--------------------------------
sem_t *make_semaphore (int n);
int sem_signal(sem_t *sem)
{
	return sem_post(sem);
}
//-----------------------------------ERROR--------------------------------------
//Error checking functions
void *check_malloc (int size);
void perror_exit(char msg[]);

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
const int ARRAY_SIZE = 10000; //warning: array_size must not be negative, 0, 1, or 2
int WORK_ARRAY[10000];



//----------------------------------START MAIN-----------------------------------
int main()
{
	printf("Hello world\n");
	void * ptr;

	//fill array with random work values
	int i = 0;
	for(i = 0; i < ARRAY_SIZE; i++) {
		WORK_ARRAY[i] = gen_rand(0, 1000);
	}

	srand(time(NULL));
	
	//test single thread time to complete
	for(i = 0; i < ARRAY_SIZE; i++) {
		usleep(WORK_ARRAY[i]);
		printf("Single thread, current element: %i, sleeping: %i\n", i, WORK_ARRAY[i]);
	}
	
	//test thread timings based on a single split of the array
	//create threads
	pthread_create(&THREADS[0], NULL, lower_thread, (void *) ptr);
	pthread_create(&THREADS[1], NULL, upper_thread, (void *) ptr);
	
	pthread_join(THREADS[0], NULL);
	pthread_join(THREADS[1], NULL);
	
	
	return 0;
	
}
//----------------------------------END MAIN--------------------------------------

sem_t *make_semaphore (int n)
{
	sem_t *sem = check_malloc (sizeof(sem_t));
	int ret = sem_init(sem, 0, n);
	if (ret == -1)
		perror_exit("sem_init failed");
	return sem;
}

void *check_malloc (int size)
{
	void *p = malloc (size);
	if(p == NULL) {
		perror ("malloc failed");
		exit(-1);
	}
	return p;
}

void perror_exit(char msg[])
{
	perror (msg);
	exit (-1);
}

//lower thread function. started by pthread_create
void *lower_thread (void *ptr) {
	int i = 0;
	for(i = 0; i < ARRAY_SIZE / 2; i++) {
		usleep(WORK_ARRAY[i]);
		printf("Lower thread, current element: %i, sleeping: %i\n", i, WORK_ARRAY[i]);
	}
}

//upper thread function. started by pthread_create
void *upper_thread (void *ptr) {
	int i = 0;
	for(i = ARRAY_SIZE / 2; i < ARRAY_SIZE; i++) {
		usleep(WORK_ARRAY[i]);
		printf("Upper thread, current element: %i, sleeping: %i\n", i, WORK_ARRAY[i]);
	}
}
