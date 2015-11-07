/**
 * Author: Jeremy Griffith
 */

#include "as5.h"

const unsigned int RAND_RANGE = RAND_MAX>>10;

extern int readcount;
extern sem_t mutex, wrt;

void easy_print(int tid, char* message) {
	printf("Thread: %d - %s\n", tid, message);
}

void *reader(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;
	easy_print(data->tid, "~~NEW READER~~");

	// Wait(mutex)
	easy_print(data->tid, "Reader is waiting on mutex"); 
	semwait(&mutex);
	readcount = readcount + 1;

	printf("Thread: %d - Reader incremented readcount to %d\n", data->tid, readcount);

	if (readcount == 1) {
		easy_print(data->tid, "Reader waits on wrt");
		semwait(&wrt);
	}
	printf("Thread: %d - Reader signals mutex\n", data->tid);
	semsignal(&mutex);
	
	// Critical Section
	printf("Thread: %d - Reader enters critical section (reading)\n", data->tid);

	// Wait(mutex)
	printf("Thread: %d - Reader waits on mutex\n", data->tid);
	semwait(&mutex);
	readcount = readcount - 1;
	printf("Thread: %d - Reader finished (decremented readcount to %d)\n", data->tid, readcount);
	
	if (readcount == 0) {
		printf("Thread: %d - Reader signals wrt\n", data->tid);
		semsignal(&wrt);
	}

	// Signal(mutex)
	printf("Thread: %d - Reader signals mutex\n", data->tid);
	semsignal(&mutex);
}

void *writer(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;

	printf("Thread: %d - ~~NEW WRITER~~\n", data->tid);

	printf("Thread: %d - Writer is waiting on wrt\n", data->tid);
	semwait(&wrt);

	printf("Thread: %d - Writer enters critical section (writing)\n", data->tid);

	printf("Thread: %d - Writer signals wrt", data->tid);
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
