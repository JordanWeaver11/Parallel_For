#include <semaphore.h>

//Error checking
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

//Semaphores
sem_t *make_semaphore (int n)
{
	sem_t *sem = check_malloc (sizeof(sem_t));
	int ret = sem_init(sem, 0, n);
	if (ret == -1)
		perror_exit("sem_init failed");
	return sem;
}

int sem_signal(sem_t *sem)
{
	return sem_post(sem);
}


