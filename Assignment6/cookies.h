/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _COOKIES_H_RPCGEN
#define _COOKIES_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct CookieStruct {
	int CanHaveCookie;
	int JudyOrTina;
};
typedef struct CookieStruct CookieStruct;

#define COOKIE_JAR 0x84467008
#define COOKIE_JAR_VERSION 1

#if defined(__STDC__) || defined(__cplusplus)
#define GET_ME_MY_COOKIE 1
extern  int * get_me_my_cookie_1(struct CookieStruct *, CLIENT *);
extern  int * get_me_my_cookie_1_svc(struct CookieStruct *, struct svc_req *);
extern int cookie_jar_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define GET_ME_MY_COOKIE 1
extern  int * get_me_my_cookie_1();
extern  int * get_me_my_cookie_1_svc();
extern int cookie_jar_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_CookieStruct (XDR *, CookieStruct*);

#else /* K&R C */
extern bool_t xdr_CookieStruct ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_COOKIES_H_RPCGEN */