/**
 * Author: Jeremy Griffith
 */

#include "as4.h"
#include <errno.h>

void withdraw(int request) {

	int semid = get_semid((key_t)SEMAPHORE_KEY);
	int shmid = get_shmid((key_t)SEMAPHORE_KEY);
	struct shared_variable_struct *shared_variables = shmat(shmid, 0, 0);

	// wait(mutex)
	printf("PID: %d - Someone is waiting on mutex to withdraw $%d.\n", getpid(), request);
	semaphore_wait(semid, SEMAPHORE_MUTEX);	
	printf("PID: %d - Withdrawer:%d has passed mutex.\n", getpid(), request);

	// if (wcount = 0 and balance > withdraw)
	if (shared_variables->wcount == 0 && shared_variables->balance >= request) {
		// {balance = balance - withdraw; signal(mutex)}
		printf("PID: %d - A withdrawal of $%d was made!\n", getpid(), request);
		shared_variables->balance = shared_variables->balance - request;
		
		printf("PID: %d - Withdrawer:%d is signaling mutex.\n", getpid(), request);
		print_memory(shared_variables);
		semaphore_signal(semid, SEMAPHORE_MUTEX);	
	} else {
		// wcount = wcount + 1;
		shared_variables->wcount = shared_variables->wcount + 1;

		// AddEndOfList(LIST, withdraw);
		printf("PID: %d - Withdrawer:%d is added to queue.\n", getpid(), request);
		insertLast(shared_variables->list, request);

		if (shared_variables->list->head == NULL) {
			printf("Totally null\n");
		}
		
		// signal(mutex);
		printf("PID: %d - Withdrawer:%d is signaling mutex.\n", getpid(),request);
		semaphore_signal(semid, SEMAPHORE_MUTEX);
		print_memory(shared_variables);
	
		// wait(wlist);
		printf("PID: %d - Withdrawer is waiting to withdraw.\n", getpid());
		semaphore_wait(semid, SEMAPHORE_WLIST);
		printf("PID: %d - Withdrawer is now ready to withdraw.\n", getpid());

		// balance = balance - FirstRequestAmount(LIST);
		shared_variables->balance = shared_variables->balance - getFirstRequestAmount(shared_variables->list);
		//printf("%d\n", shared_variables->balance);
		// DeleteFirstRequest(LIST);
		removeFirst(shared_variables->list);

		// wcount = wcount - 1;
		shared_variables->wcount = shared_variables->wcount - 1;		

		// if (wcount > 1 and (FirstRequestAmount(LIST)) < balance)) signal(wlist)
		if (shared_variables->wcount > 0 && getFirstRequestAmount(shared_variables->list) < shared_variables->balance) {
	
			printf("PID: %d - Withdrawer is signaling the next withdrawer.\n", getpid());
			print_memory(shared_variables);
			semaphore_signal(semid, SEMAPHORE_WLIST);		
		}		

		//	else signal(mutex)}
		else {
			printf("PID: %d - Withdrawer is signaling mutex.\n", getpid());
			print_memory(shared_variables);
			semaphore_signal(semid, SEMAPHORE_MUTEX);
		}
	}

	if (shmdt(shared_variables) == -1) {
		perror("shmdt failed during a withdraw");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
