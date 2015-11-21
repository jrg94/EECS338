/**
 * Author: Jeremy Griffith
 * Assignment 6 Client-Judy
 */

#ifndef CLIENT_JUDY
#define CLIENT_JUDY

#include "as6.h"

int askForCookies(CLIENT *c) {
	struct CookieStruct cs = {0, JUDY};
	
	int *result = get_me_my_cookie_1(&cs, c);
	
	return *result;
}

/*
int main(int argc, char* argv[]) {
	srand(time(NULL));
	CLIENT *c;

	// Test inputs
	if (argc != 2) {
		// Print error
		return EXIT_FAILURE;
	}

	// Create client
	char* server = argv[1];
	c = clnt_create(server, 
}*/

#endif /* CLIENT_JUDY */
