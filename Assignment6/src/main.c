/**
 * Author: Jeremy Griffith
 */
#include "as6.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));
	CLIENT *c;

	if (argc != 2) {
		// Print error
	}

	char *server = argv[1];
	c = clnt_create(server, COOKIE_JAR, COOKIE_JAR_VERSION, "udp");
	if (c == NULL) {
		// Print error & exit
		exit(EXIT_FAILURE);
	}

	clnt_destroy(c);
	return 0;
}
