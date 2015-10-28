/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

void print_memory(struct shared_variable_struct *shared) {
	printf("PID: %d - Shared variable status:\n", getpid());
	printf("*** balance = %d, wcount = %d\n", shared->balance, shared->wcount);
	printf("*** list: ");
	printList(shared->list);
}
