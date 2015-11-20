/**
 * The server code
 */ 
#include "as6.h"

int *get_me_my_cookie_1_svc(struct CookieStruct *request, struct svc_req *rqstp) {

	static int response;
	response = 1;
	return(&response);
}
