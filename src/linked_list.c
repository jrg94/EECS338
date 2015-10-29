/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

/**
 * An insertion function for linked lists
 */
void insertLast(struct linked_list *list, int request) {
	
	// Generates a new node pointer
	struct node *insertNode = (struct node*)malloc(sizeof(struct node));

	// Tests the pointer for null
	if (insertNode == NULL) {
		perror("Failed to allocate memory when inserting a node");
		exit(EXIT_FAILURE);
	}

	// Initialize the new node
	insertNode->request = request;
	insertNode->next = NULL;

	// Handles first insert case
	if (list->head == NULL) {
		list->head = insertNode;
	}
	else {

		struct node * current = list->head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = insertNode;
	}
}

/**
 * Removes the first node from the list
 */
void removeFirst(struct linked_list *list) {
	
	struct node *newHead = list->head->next;
	free(list->head);
	list->head = newHead;
}

int getFirstRequestAmount(struct linked_list *list) {

	if (list->head == NULL) {
		printf("Failed to get request amount from head because head is null.\n");
		exit(EXIT_SUCCESS);
	}

	return list->head->request;
}

void printList(struct linked_list *list) {
	struct node *temp = list->head;
//	if (temp == NULL) { printf("head is null\n"); }
	while (temp != NULL) {
		printf("%d -> ", temp->request);
		temp = temp->next;
	}
	printf("\n");
}
