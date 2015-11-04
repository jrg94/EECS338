/**
 * Author: Jeremy Griffith
 */

#include "as5.h"

const unsigned int RAND_RANGE = RAND_MAX>>10;

extern int readcount;
extern sem_t mutex, wrt;

void *reader(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;

	// Wait(mutex)
	semwait(&mutex);
	readcount = readcount + 1;

	printf("Thread: %d - A new reader! (incremented readcount to %d)\n", data->tid, readcount);

	if (readcount == 1) {
		printf("Thread: %d - Reader waits on wrt\n", data->tid);
		semwait(&wrt);
	}
	
	// Critical Section
	printf("Thread: %d - Reader enters critical section (reading)\n", data->tid);

	// Wait(mutex)
	semwait(&mutex);
	readcount = readcount - 1;
	printf("Thread: %d - Reader finished (decremented readcount to %d)\n", data->tid, readcount);
	
	if (readcount == 0) {
		printf("Thread: %d - Reader signals wrt\n", data->tid);
		semsignal(&wrt);
	}

	// Signal(mutex)
	semsignal(&mutex);
}

void *writer(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;

	printf("Thread: %d - A new writer!", data->tid);

	semwait(&wrt);

	printf("Thread: %d - Writer enters critical section (writing)\n", data->tid);

	semsignal(&wrt);
}

/**
 * A random number generating function based on the solution
 * to the Spring 2015 banking problem
 */
int getRand() {
	return ((rand() % RAND_RANGE) - RAND_RANGE/2);
}

/**
 * A wrapper function based on the solution
 * to the Spring 2015 banking problem
 */
void semwait(sem_t *sem) {
	if (sem_wait(sem) < 0) {
		perror("sem_wait in semwait call failed");
		exit(EXIT_FAILURE);
	}
}

/**
 * A wrapper function based on the solution
 * to the Spring 2015 banking problem
 */
void semsignal(sem_t *sem) {
	if(sem_post(sem) < 0) {
		perror("sem_post in semsignal call failed");
		exit(EXIT_FAILURE);
	}
}
