/**
 * Author: Jeremy Griffith
 *
 * The overall header file for the program
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_OF_THREADS 200

// Functions
void semwait(sem_t *sem);
void semsignal(sem_t *sem);

// Structures
typedef struct _thread_data_t {
	int tid;
} thread_data_t;
