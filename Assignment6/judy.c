/**
 * Author: Jeremy Griffith
 * Assignment 6 Client-Judy
 */

#ifndef CLIENT_JUDY
#define CLIENT_JUDY

#include "as6.h"

/**
 * Overrides the askForCookies function
 * which is used to differentiate 
 * between the two client processes
 */
int askForCookies(CLIENT *c) {
	struct CookieStruct cs = {0, JUDY};
	
	int *result = get_me_my_cookie_1(&cs, c);
	
	return *result;
}

#endif /* CLIENT_JUDY */
