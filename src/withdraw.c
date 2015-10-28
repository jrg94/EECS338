/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

void withdraw(int request) {

	int semid = get_semid((key_t)SEMAPHORE_KEY);
	int shmid = get_shmid((key_t)SEMAPHORE_KEY);
	struct shared_variable_struct *shared_variables = shmat(shmid, 0, 0);

	// wait(mutex)
	printf("PID: %d - Someone is waiting on mutex to withdraw.\n", getpid());
	semaphore_wait(semid, SEMAPHORE_MUTEX);	
	printf("PID: %d - Withdrawer has passed mutex.\n", getpid());

	// if (wcount = 0 and balance > withdraw)
	if (shared_variables->wcount == 0 && shared_variables->balance > request) {
	//	{balance = balance - withdraw; signal(mutex)}
		shared_variables->balance = shared_variables->balance + request;
		
		printf("PID: %d - Withdrawer is signaling mutex.\n", getpid());
		semaphore_signal(semid, SEMAPHORE_MUTEX);	
	}	
	
	// else {

	else {
		// wcount = wcount + 1;
		shared_variables->wcount = shared_variables->wcount + 1;
		
		// AddEndOfList(LIST, withdraw);
		insertLast(shared_variables->list, request);

		//	signal(mutex);
		printf("PID: %d - Withdrawer is signaling mutex.\n", getpid());
		semaphore_signal(semid, SEMAPHORE_MUTEX);
	
		//	wait(wlist);
		printf("PID: %d - Withdrawer is waiting to withdraw.\n", getpid());
		semaphore_wait(semid, SEMAPHORE_WLIST);
		printf("PID: %d - Withdrawer is now ready to withdraw.\n", getpid());

		//	balance = balance - FirstRequestAmount(LIST);
		shared_variables->balance = shared_variables->balance - getFirstRequestAmount(shared_variables->list);

		// 	DeleteFirstRequest(LIST);
		removeFirst(shared_variables->list);

		// 	wcount = wcount - 1;
		shared_variables->wcount = shared_variables->wcount + 1;		

		//	if (wcount > 1 and (FirstRequestAmount(LIST)) < balance)) signal(wlist)
		if (shared_variables->wcount > 1 && getFirstRequestAmount(shared_variables->list) < shared_variables->balance) {
	
			printf("PID: %d - Withdrawer is signaling the next withdrawer.\n", getpid());
			semaphore_signal(semid, SEMAPHORE_WLIST);		
		}		

		//	else signal(mutex)}
		else {
			printf("PID: %d - Withdrawer is signaling mutex.\n", getpid());
			semaphore_signal(semid, SEMAPHORE_MUTEX);
		}
	}
}
