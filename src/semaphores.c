/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

/**
 * A wrapper function modeled after the wrappers seen in
 * the cars example code
 *
 * Used for getting a semaphore
 */
int get_semid(key_t semkey) {
	int value = semget(semkey, NUMBER_OF_SEMAPHORES, 0777 | IPC_CREAT);
	if (value == -1) {
		perror("get_semid failed while calling semget");
		exit(EXIT_FAILURE);
	}
	return value;
}

/**
 * A wrapper function modeled after the wrappers seen in 
 * the cars example code
 * 
 * Used for getting shared memory
 */
int get_shmid(key_t shmkey) {
	int value = shmget(shmkey, sizeof(struct shared_variable_struct), 0777 | IPC_CREAT);
	if (value == -1) {
		perror("get_shmid failed while calling shmget");
		exit(EXIT_FAILURE);
	}
	return value;
}

/**
 * A wrapper function modeled after the wrappers seen in 
 * the cars example code
 *
 * Used to make a function for calling wait on a semaphore
 */
void semaphore_wait(int semid, int semnumber) {
	
	struct sembuf wait_buffer;

	wait_buffer.sem_num = semnumber;

	wait_buffer.sem_op = -1;
	wait_buffer.sem_flg = 0;

	if (semop(semid, &wait_buffer, 1) == -1) {
		perror("The semaphore_wait function failed");
		exit(EXIT_FAILURE);
	}	
}

/**
 * A wrapper function modeled after the wrappers seen in
 * the cars example code
 *
 * Used to make a function for calling signal on a semaphore
 */
void semaphore_signal(int semid, int semnumber) {
	
	struct sembuf signal_buffer;

	signal_buffer.sem_num = semnumber;
	
	signal_buffer.sem_op = 1;
	signal_buffer.sem_flg = 0;

	if (semop(semid, &signal_buffer, 1) == -1) {
		perror("The semaphore_signal function failed");
		exit(EXIT_FAILURE);
	}

}

void process_fork(int deposit_or_withdraw, int request) {
	pid_t child_pid;
	child_pid = fork();

	if (child_pid == -1) {
		perror("Failed to fork process!\n");
		exit(EXIT_FAILURE);
	}
}
