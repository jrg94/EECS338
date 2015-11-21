/**
 * Author: Jeremy Griffith
 */
#include "as6.h"

inline void printInfo() {
        char hostname[256];

        gethostname(hostname, sizeof hostname);

        char fmt[64], buf[64];
        struct timeval tv;
        struct tm *tm;

        gettimeofday(&tv, NULL);
        if ((tm = localtime(&tv.tv_sec)) != NULL) {
                strftime(fmt, sizeof fmt, "%H:%M:%S.%%03u", tm);
                snprintf(buf, sizeof buf, fmt, tv.tv_usec);
        }

        printf("%s-%s-%d: ", buf, hostname, getpid());
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	CLIENT *c;

	// Test input
	if (argc != 2) {
		// Print error
		printInfo();
		printf("Not enough inputs\n");
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
