/**
 * Author: Jeremy Griffith
 */

#include "as4.h"

/**
 * An insertion function for linked lists
 */
void insertLast(struct node *head, int request) {
	
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
	if (head->next == NULL) {
		head->next = insertNode;
	}

	struct node *traverse = head;
	while (traverse != NULL) {
		traverse = traverse->next;
	}
	traverse->next = insertNode;
}

/**
 * Removes the first node from the list
 */
void removeFirst(struct node *head) {
	struct node *newHead = head->next;
	free(head);
	head = newHead;
}

int getFirstRequestAmount(struct node *head) {
	return head->request;
}
