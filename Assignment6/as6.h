/**
 * Author: Jeremy Griffith
 * Assignment 6 Header
 */

#include "cookies.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_COOKIES 20

#define TINA 1
#define JUDY 2

int askForCookies(CLIENT *c);

/**
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
}*/
