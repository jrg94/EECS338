/**
 * Author: Jeremy Griffith
 */

#include "as5.h"

const unsigned int RAND_RANGE = RAND_MAX>>10;

extern int readcount;
extern sem_t mutex, wrt;

/**
 * A convenience function for printing messages
 * about each thread
 */
void easy_print(int tid, char* message) {
	printf("Thread: %d - %s\n", tid, message);
}

/**
 * A convenience function for stalling a
 * thread
 */
void thread_rest() {
	struct timespec time = 
	{
		0,
		100000000L
	};

	if (nanosleep(&time, NULL) < 0) {
		fprintf(stderr, "nanosleep failed in thread_rest\n");
	}
}

/**
 * A function which serves as a reader thread
 */
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
	easy_print(data->tid, "Reader signals mutex");
	semsignal(&mutex);
	
	// Critical Section
	easy_print(data->tid, "Reader enters critical section");
	thread_rest();

	// Wait(mutex)
	easy_print(data->tid, "Reader waits on mutex");
	semwait(&mutex);

	readcount = readcount - 1;
	printf("Thread: %d - Reader finished (decremented readcount to %d)\n", data->tid, readcount);
	
	if (readcount == 0) {
		easy_print(data->tid, "Reader signals wrt");
		semsignal(&wrt);
	}

	// Signal(mutex)
	easy_print(data->tid, "Reader signals mutex");
	semsignal(&mutex);
}

/**
 * A function which serves as a writer thread
 */
void *writer(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;

	easy_print(data->tid, "~~NEW WRITER~~");

	// Wait on wrt
	easy_print(data->tid, "Writer is waiting on wrt");
	semwait(&wrt);

	// Critical Section
	easy_print(data->tid, "Writer enters critical section");
	thread_rest();

	// Signal wrt
	easy_print(data->tid, "Writer signals wrt");
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
