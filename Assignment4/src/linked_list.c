/**
 * Author: Jeremy Griffith
 * 
 * This file is responsible for handling linked lists
 * Functionality includes adding items to the end of a list,
 * removing the first item, printing the list, and returning 
 * the first item.
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

/**
 * Retrieves the first value from the head of the linked list
 */
int getFirstRequestAmount(struct linked_list *list) {

	if (list == NULL) {
		printf("List is null\n");
	}

	else if (list->head == NULL) {
		printf("Failed to get request amount from head because head is null.\n");
	}
	else {
		return list->head->request;
	}

	return 0;
}

/**
 * A debug tool which prints out a linked list
 */
void printList(struct linked_list *list) {
	struct node *temp = list->head;

	while (temp != NULL) {
		printf("%d -> ", temp->request);
		temp = temp->next;
	}
	printf("\n");
}
