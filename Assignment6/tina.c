/**
 * Author: Jeremy Griffith
 * Assignment 6 Client-Tina
 */
#ifndef CLIENT_TINA
#define CLIENT_TINA

#include "as6.h"

int askForCookies(CLIENT *c) {
	
	struct CookieStruct cs = {0, TINA};

	int* result = get_me_my_cookie_1(&cs, c);
	
	return *result;
}

#endif

