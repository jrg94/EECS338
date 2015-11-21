/**
 * Author: Jeremy Griffith
 * Assignment 6 Client-Tina
 */
#ifndef CLIENT_TINA
#define CLIENT_TINA

#include "as6.h"

int askForCookies(CLIENT *c) {
	
	struct CookieStruct cs = {0, TINA};

	int* result = get_me_my_cookie_1(&cs, c);
	
	return *result;
}

/*
int main(int argc, char* argv[]) {
	srand(time(NULL));
	CLIENT *c;

	// User did not enter the correct information
	if (argc != 2) {
		// Print error
		return EXIT_FAILURE;
	}

	// Create client
	char* server = argv[1];
	c = clnt_create(server, COOKIE_JAR, COOKIE_JAR_VERSION, "udp");
	if (c == NULL) {
		clnt_pcreateerror("Could not create a Tina client");
		exit(EXIT_FAILURE);
	}

	// Insert cookie loop

	clnt_destroy(c);
	return EXIT_SUCCESS;
}*/

#endif

