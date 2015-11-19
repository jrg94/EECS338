/**
 * Author: Jeremy Griffith
 * 
 * The header file which links 
 * all of the object files together
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define SEMAPHORE_KEY           0xFA2B

// The location of the semaphores in the semaphore list
#define SEMAPHORE_MUTEX         0
#define SEMAPHORE_WLIST         1
#define NUMBER_OF_SEMAPHORES    2

// A definition for the two types of processes
#define WITHDRAW	1
#define DEPOSIT		2

// Integers for stalling
#define STALL_TIME	2

// Functions
int get_semid(key_t semkey);
int get_shmid(key_t shmkey);

// The shared memory struct
struct shared_variable_struct {
	int wcount;
	int balance;
	struct linked_list *list;
};

// A linked list struct
struct linked_list {
	struct node *head;
};

// The semun union
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

// A node struct
struct node {
	int request;
	struct node *next;
};

 
