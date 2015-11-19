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
void easy_print(int tid, char* message, char* time) {
	if (time == 0) {
		printf("Thread: %d - %s\n", tid, message);
	}
	else {
		printf("Thread: %d - %s @ %s\n", tid, message, time);
	}
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
 * Retrieves the current time and returns it as a string
 */
char* get_time() {
	struct timeval tval;
	char output[35];

	gettimeofday(&tval, NULL);	

	sprintf(output, "%d.%d", (int)tval.tv_sec, (int)tval.tv_usec);

	char* str = output;
	return str;
}

/**
 * A function which serves as a reader thread
 */
void *reader(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;
	easy_print(data->tid, "~~NEW READER~~", get_time());

	// Wait(mutex)
	easy_print(data->tid, "Reader is waiting on mutex", NULL); 
	semwait(&mutex);
	readcount = readcount + 1;

	printf("Thread: %d - Reader incremented readcount to %d\n", data->tid, readcount);

	if (readcount == 1) {
		easy_print(data->tid, "Reader waits on wrt", NULL);
		semwait(&wrt);
	}
	easy_print(data->tid, "Reader signals mutex", NULL);
	semsignal(&mutex);
	
	// Critical Section
	easy_print(data->tid, "Reader enters critical section", NULL);
	thread_rest();

	// Wait(mutex)
	easy_print(data->tid, "Reader waits on mutex", NULL);
	semwait(&mutex);

	readcount = readcount - 1;
	printf("Thread: %d - Reader finished (decremented readcount to %d)\n", data->tid, readcount);
	
	if (readcount == 0) {
		easy_print(data->tid, "Reader signals wrt", NULL);
		semsignal(&wrt);
	}

	// Signal(mutex)
	easy_print(data->tid, "Reader signals mutex", get_time());
	semsignal(&mutex);
}

/**
 * A function which serves as a writer thread
 */
void *writer(void *arg) {
	thread_data_t *data = (thread_data_t *)arg;

	easy_print(data->tid, "~~NEW WRITER~~", get_time());

	// Wait on wrt
	easy_print(data->tid, "Writer is waiting on wrt", NULL);
	semwait(&wrt);

	// Critical Section
	easy_print(data->tid, "Writer enters critical section", NULL);
	thread_rest();

	// Signal wrt
	easy_print(data->tid, "Writer signals wrt", get_time());
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
