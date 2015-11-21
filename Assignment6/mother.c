/**
 * The server code
 */ 
#include "as6.h"

static int totalCookies = -1;
static int consecutiveTinaCookies = 0;

int *get_me_my_cookie_1_svc(struct CookieStruct *request, struct svc_req *rqstp) {

	// Initialize cookie jar
	if (totalCookies < 0) {
		totalCookies = MAX_COOKIES;
		printf("Mother is initialized. Cookie jar contains %d cookies\n", totalCookies);
	}

	// If Judy is requesting a cookie
	// Must wait for Tina to have two cookies
	if(request->JudyOrTina == JUDY) {
		static int response;

		// If cookie jar is empty
		if (totalCookies == 0) {
			printf("Judy requested a cookie, but the cookie jar is empty.\n");
			response = -2;
			return(&response);
		}

		// If Tina hasn't had at least two cookies since Judy's last cookie
		else if (consecutiveTinaCookies < 2) {
			printf("Judy requested a cookie before Tina had two cookies\n");
			response = -1;
			return(&response);
		}

		// Otherwise, Judy can have a cookie
		else {
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
			printf("Tina requested a cookie, but the cookie jar is empty.\n");
			response = -2;
			return(&response);
		}

		else {
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
