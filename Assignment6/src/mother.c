/**
 * The server code
 */ 
#include "as6.h"

static int totalCookies = -1;

int *get_me_my_cookie_1_svc(struct CookieStruct *request, struct svc_req *rqstp) {

	// Initialize cookie jar
	if (totalCookies < 0) {
		totalCookies = MAX_COOKIES;
		printf("Mother is initialized. Cookie jar contains %d cookies\n", totalCookies);
	}

	// If Judy is requesting a cookie
	if(request->JudyOrTina == JUDY) {

	}

	// If Tina is requesting a cookie
	if(request->JudyOrTina == TINA) {

	}

	static int response;
	response = 1;
	return(&response);
}
