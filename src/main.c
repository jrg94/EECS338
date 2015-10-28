/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

int main(int argc, char *argv[]) {
	
	// Begin creation of semaphores
	union semun semaphore_values;

	// Initialize semaphores
	unsigned short semaphore_init_values[NUMBER_OF_SEMAPHORES];
	semaphore_init_values[SEMAPHORE_MUTEX] = 1;
	semaphore_init_values[SEMAPHORE_WLIST] = 0;
	semaphore_values.array = semaphore_init_values;

	// Create semaphores
	int semid = get_semid((key_t)SEMAPHORE_KEY);
	if (semctl(semid, SEMAPHORE_MUTEX, SETALL, semaphore_values) == -1) {
		perror("Failed to create semaphores in main");
		exit(EXIT_FAILURE);
	}

	// Create Shared Memory
	int shmid = get_shmid((key_t)SEMAPHORE_KEY);
	struct shared_variable_struct *shared_variables = shmat(shmid, 0, 0);

	// Initialize Shared Memory
	shared_variables->wcount = 0;
	shared_variables->balance = 500;
	shared_variables->list = NULL;

	
}
