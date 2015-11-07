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

// Functions
void *reader(void *arg);
void *writer(void *arg);

int main(int argc, char* argv[]) {
	// Generates an array of threads and the associated thread data
	pthread_t threads[NUM_OF_THREADS];
	thread_data_t thread_data[NUM_OF_THREADS];

	// A variable for error checking thread creation
	int errorCheck;

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

		// Generates a reader if getRand() is negative
		if (getRand() < 0) {
			thread_func = reader;
		}
		// Otherwise, generate a writer
		else {
			thread_func = writer;
		}
		
		if ((errorCheck = pthread_create(&threads[i], NULL, thread_func, &thread_data[i]))) {
			fprintf(stderr, "Failed to create a thread, %d\n", errorCheck);
			return EXIT_FAILURE;
		}
	}
	sleep(12);
	printf("*** LAST THREAD INCOMING (%d) ***\n", NUM_OF_THREADS+1);
	fflush(stdout);
	sleep(1);
	printf(".");
	fflush(stdout);
	sleep(1);
	printf(".");
	fflush(stdout);
	sleep(1);
	printf(".");
	fflush(stdout);
	sleep(1);
	printf("\n");
	pthread_t finalThread;
	thread_data_t fTData = { NUM_OF_THREADS + 1 };

	// Creates the final thread
	if ((errorCheck = pthread_create(&finalThread, NULL, writer, &fTData))) {
		fprintf(stderr, "pthread_create failed in main, %d\n", errorCheck);
		return EXIT_FAILURE;
	}

	// Waits until all threads terminate
	for (i = 0; i < NUM_OF_THREADS; i++) {
		if ((errorCheck = pthread_join(threads[i], NULL))) {
			fprintf(stderr, "pthread_join failed in man, %d\n", errorCheck);
		}
	}

	// Waits until the final thread terminates
	if ((errorCheck = pthread_join(finalThread, NULL))) {
		fprintf(stderr, "pthread_join failed, %d\n", errorCheck);
	}

	return EXIT_SUCCESS;
}
