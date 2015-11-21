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
		printf("Not enough inputs\n");
		printf("Try: ./<executable> <server>\n");
		exit(EXIT_FAILURE);
	}

	// Create client
	char *server = argv[1];
	c = clnt_create(server, COOKIE_JAR, COOKIE_JAR_VERSION, "udp");
	if (c == NULL) {
		// Print error & exit
		clnt_pcreateerror("Could not create client");
		exit(EXIT_FAILURE);
	}

	// Begin asking for cookies
	while (1) {
		printf("Requesting a cookie\n");
		int response = askForCookies(c);
		
		// Cookie jar is empty
		if (response == -2) {
			printf("Cookie jar is empty\n");
			break;
		}
		// Judy has to wait
		else if (response == -1) {
			printf("Judy must wait until Tina has 2 cookies\n");
			continue;
		}
		// Free to take a cookie
		else if (response == 1) {
			printf("Got a cookie\n");
			continue;
		}
		
		sleep(1);
	}

	clnt_destroy(c);
	return 0;
}
