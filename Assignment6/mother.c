/**
 * The server code
 * The mother is in charge of the cookie jar
 * She determines who gets fed cookies
 */ 
#include "as6.h"

static int totalCookies = -1;
static int consecutiveTinaCookies = 0;

/**
 * A handy function for printing out
 * imformation about this remote procedure
 */
void printInfo() {
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

/**
 * Provides the cookie jar functionality server side
 */
int *get_me_my_cookie_1_svc(struct CookieStruct *request, struct svc_req *rqstp) {

	// Initialize cookie jar
	if (totalCookies < 0) {
		totalCookies = MAX_COOKIES;
		printInfo();
		printf("Mother is initialized. Cookie jar contains %d cookies\n", totalCookies);
	}

	// If Judy is requesting a cookie
	// Must wait for Tina to have two cookies
	if(request->JudyOrTina == JUDY) {
		static int response;

		// If cookie jar is empty
		if (totalCookies == 0) {
			printInfo();
			printf("Judy requested a cookie, but the cookie jar is empty.\n");
			response = -2;
			return(&response);
		}

		// If Tina hasn't had at least two cookies since Judy's last cookie
		else if (consecutiveTinaCookies < 2) {
			printInfo();
			printf("Judy requested a cookie before Tina had two cookies\n");
			response = -1;
			return(&response);
		}

		// Otherwise, Judy can have a cookie
		else {
			printInfo();
			printf("Judy requested a cookie and received it\n");
			consecutiveTinaCookies = 0;
			totalCookies--;
			response = 1;
			return(&response);			
		}
	}

	// If Tina is requesting a cookie
	// Can have cookie whenever she wants
	if(request->JudyOrTina == TINA) {
		static int response;

		// If cookie jar is empty
		if (totalCookies == 0) {
			printInfo();
			printf("Tina requested a cookie, but the cookie jar is empty.\n");
			response = -2;
			return(&response);
		}

		else {
			printInfo();
			printf("Tina requested a cookie and received it\n");
			totalCookies--;
			consecutiveTinaCookies++;
			response = 1;
			return(&response);
		}
	}

	static int response;
	response = 1;
	return(&response);
}
