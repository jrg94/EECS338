/**
 * Author: Jeremy Griffith
 * Assignment 6 Main
 */

#include "as6.h"

int main (int argc, char * argv[]) {

	char *server;
	CLIENT *c;

	// Test the command line input
	if (argc != 2) {
		printf("A server name was not specified\n");
		printf("Try %s <server name>\n", argv[0]);
		exit(1);
	}

	// Create client
	server = argv[1];
	c = clnt_create(server, COOKIE_JAR, COOKIE_JAR_VERSION, "udp"); 
	if(c == NULL) {
		clnt_pcreateerror("Error creating client");
		exit(EXIT_FAILURE);
	} 

	clnt_destroy(c);
	return 0;
}
