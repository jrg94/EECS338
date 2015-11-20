/**
 * Author: Jeremy Griffith
 * Assignment 6 Main
 */

#include "as6.h"

char *server;
char machine[200];
char username[256];

int main (int argc, char * argv[]) {

	CLIENT *c;

	// Test the command line input
	if (argc != 2) {
		printf("A server name was not specified\n");
		printf("Try %s <server name>\n", argv[0]);
		exit(1);
	}

	// Store the server name
	server = argv[1];

	// An RPC function for retrieving the hostname
	gethostname(machine, 200);
	snprintf(username, 256, "%s%d", machine, getpid());

	// Begin program functionality

	c = clnt_create(server, 

	clnt_destroy(c);
	return 0;
}
