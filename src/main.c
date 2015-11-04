/**
 * @Author: Jeremy Griffith
 *
 * The entry file for the program
 */

#include "as5.h"

// Shared Variables
sem_t mutex, wrt;
int readcount;

time_t t;

int main(int argc, char* argv[]) {
	// Generates an array of threads and the associated thread data
	pthread_t threads[NUM_OF_THREADS];
	thread_data_t thread_data[NUM_OF_THREADS];

	srand((unsigned int)time(&t));

	// Tests semaphore creation
	if (sem_init(&mutex, 0, (unsigned int)1) < 0
		|| sem_init(&wrt, 0, (unsigned int)1) < 0) {
		perror("sem_init failed");
		exit(EXIT_FAILURE);
	}

	int i;
	for (i = 0; i < NUM_OF_THREADS; i++) {
		void *thread_func;

		thread_data[i].tid = i;
	}	
}
