/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

void test1();
void test2();

void print_memory(struct shared_variable_struct *shared) {
	printf("*** PID: %d - Shared variable status\n", getpid());
	printf("*** balance = %d, wcount = %d\n", shared->balance, shared->wcount);
	printf("*** list: ");
	printList(shared->list);
}

void test(int test) {
	switch (test) {
		case 1:
			test1();
			break;
		case 2:
			test2();
			break;
		default:
			printf("Failed to choose a valid test\n");
			exit(EXIT_FAILURE);
	}
}

/**
 * Tests behavior where withdraws are all legal
 */
void test1() {
        process_fork(DEPOSIT, 100);
        sleep(STALL_TIME);
        process_fork(DEPOSIT, 200);
        sleep(STALL_TIME);
        process_fork(WITHDRAW, 200);
        sleep(STALL_TIME);
	process_fork(WITHDRAW, 500);
	sleep(STALL_TIME);
	process_fork(DEPOSIT, 500);
	sleep(STALL_TIME);
	process_fork(DEPOSIT, 1000);

	int i;
	for (i = 0; i < 6; i++) {
        	wait(NULL);
        }
}

void test2() {
	process_fork(WITHDRAW, 600);
	sleep(STALL_TIME);
	process_fork(DEPOSIT, 700);
	sleep(STALL_TIME);
	process_fork(WITHDRAW, 200);
	sleep(STALL_TIME);

	wait(NULL);
	wait(NULL);
	wait(NULL);
}
