/**
 * Author: Jeremy Griffith
 */
#include "as6.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));
	CLIENT *c;

	// Test input
	if (argc != 2) {
		// Print error
	}

	// Create client
	char *server = argv[1];
	c = clnt_create(server, COOKIE_JAR, COOKIE_JAR_VERSION, "udp");
	if (c == NULL) {
		// Print error & exit
		exit(EXIT_FAILURE);
	}

	// Begin asking for cookies
	while (1) {
		askForCookies(c);
	}

	clnt_destroy(c);
	return 0;
}
