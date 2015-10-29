/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

/**
 * An insertion function for linked lists
 */
void insertLast(struct node **head, int request) {
	int shmid;
		
	// Generates a new node pointer
	
	if ((shmid = shmget((key_t)SEMAPHORE_KEY + 1, sizeof(struct node), 0666 | IPC_CREAT)) < 0) {
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	struct node *insertNode = shmat(shmid, 0,0); //(struct node*)malloc(sizeof(struct node));

	// Tests the pointer for null
	if (insertNode == NULL) {
		perror("Failed to allocate memory when inserting a node");
		exit(EXIT_FAILURE);
	}

	// Initialize the new node
	insertNode->request = request;
	insertNode->next = NULL;

	// Handles first insert case
	if ((*head)->next == NULL) {
		(*head)->request = request;
		(*head)->next = NULL;
	//	printf("%d\n", head->request);
	}
	else {

		struct node * current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = insertNode;
	}
}

/**
 * Removes the first node from the list
 */
void removeFirst(struct node *head) {
	struct node *newHead = head->next;
//	free(head);
	head = newHead;
}

int getFirstRequestAmount(struct node *head) {

	if (head == NULL) {
		printf("Failed to get request amount from head because head is null.\n");
		exit(EXIT_SUCCESS);
	}

	return head->request;
}

void printList(struct node *head) {
	struct node *temp = head;
//	if (temp == NULL) { printf("head is null\n"); }
	while (temp != NULL) {
		printf("%d -> ", temp->request);
		temp = temp->next;
	}
	printf("\n");
}
