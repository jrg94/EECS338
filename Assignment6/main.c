/**
 * Author: Jeremy Griffith
 * 
 * Serves as the main function for both
 * client processes
 */
#include "as6.h"

/**
 * A handy function for printing out
 * imformation about this remote procedure
 */ 
void printInfo() {
        char hostname[256];

	// Retrieves the machine name
        gethostname(hostname, sizeof hostname);

        char fmt[64], buf[64];
        struct timeval tv;
        struct tm *tm;

	// Retrieves the time of day
        gettimeofday(&tv, NULL);
        if ((tm = localtime(&tv.tv_sec)) != NULL) {
                strftime(fmt, sizeof fmt, "%H:%M:%S.%%03u", tm);
                snprintf(buf, sizeof buf, fmt, tv.tv_usec);
        }

	// Outputs the time, hostname, and pid for this process
        printf("%s-%s-%d: ", buf, hostname, getpid());
}

/**
 * The client main function
 */
int main(int argc, char* argv[]) {
	srand(time(NULL));
	CLIENT *c;

	// Test input
	if (argc != 2) {
		// Print error
		printInfo();
		printf("Not enough inputs -> ");
		printf("Try: ./<executable> <server>\n");
		exit(EXIT_FAILURE);
	}

	// Create client
	char *server = argv[1];
	c = clnt_create(server, COOKIE_JAR, COOKIE_JAR_VERSION, "udp");
	if (c == NULL) {
		// Print error & exit
		printInfo();
		clnt_pcreateerror("Could not create client");
		exit(EXIT_FAILURE);
	}

	// Begin asking for cookies
	while (1) {
		printInfo();
		printf("Requesting a cookie\n");
		int response = askForCookies(c);
		
		// Cookie jar is empty
		if (response == -2) {
			printInfo();
			printf("Cookie jar is empty\n");
			break;
		}
		// Judy has to wait
		else if (response == -1) {
			printInfo();
			printf("Judy must wait until Tina has 2 cookies\n");
		}
		// Free to take a cookie
		else if (response == 1) {
			printInfo();
			printf("Got a cookie\n");
		}
		
		fflush(stdout);
		sleep(1);
		printInfo();
		printf("Finished\n");
	}

	clnt_destroy(c);
	return 0;
}
