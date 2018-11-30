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



void *lower_thread (void *ptr);
void *upper_thread (void *ptr);

//----------------------------------START MAIN-----------------------------------
int main()
{
	printf("Hello world\n");
	/*
	//Create threads
	for (i = 0; i < NUM_THINKERS; i++) {
		pthread_create(&THINKERS[i].threadID, NULL, philosopher_action, (void *) &THINKERS[i]);
	}
	//Block until all threads are finished
	for(i = 0; i < NUM_THINKERS; i++) {
		pthread_join(THINKERS[i].threadID, NULL);
	}
	*/
	void * ptr;
	pthread_t THREADS[2];
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

void *lower_thread (void *ptr) {
	
}

void *upper_thread (void *ptr) {
	
}
