/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

void deposit(int deposit) {
	printf("PID: %d - Someone wants to deposit $%d!\n", getpid(), deposit);

	// Store semaphores and shared memory
	int semid = get_semid((key_t)SEMAPHORE_KEY);
	int shmid = get_shmid((key_t)SEMAPHORE_KEY);
	struct shared_variable_struct *shared_variables = shmat(shmid, 0, 0);

	// wait(mutex)
	printf("PID: %d - Depositer:%d is waiting on mutex.\n", getpid(), deposit);
	semaphore_wait(semid, SEMAPHORE_MUTEX);
	printf("PID: %d - Depositer:%d has passed mutex.\n", getpid(), deposit);

	// balance = balance + deposit
	shared_variables->balance = shared_variables->balance + deposit;

	// if (wcount = 0) signal(mutex)
	if (shared_variables->wcount == 0) {
		printf("PID: %d - Depositer:%d is signaling mutex\n", getpid(), deposit);
		print_memory(shared_variables);
		semaphore_signal(semid, SEMAPHORE_MUTEX);
	}

	// else if (FirstRequestAmount(LIST > balance) signal(mutex)
	else if (getFirstRequestAmount(shared_variables->list) > shared_variables->balance) {
                printf("PID: %d - Depositer:%d is signaling mutex\n", getpid(), deposit);
                semaphore_signal(semid, SEMAPHORE_MUTEX);
	}

	// else signal(wlist)
	else {
		printf("PID: %d - Depositer is signaling the wait list\n", getpid());
		semaphore_signal(semid, SEMAPHORE_WLIST);
	}

	if (shmdt(shared_variables) == -1) {
		perror("shmdt failed at end of deposit");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
